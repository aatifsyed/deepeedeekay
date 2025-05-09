//! A [`Packet`] is a linked list of [`Segment`]s,
//! storing data received from a [`port`](crate::port).
//!
//! Packets may be allocated by [`Pool`]s.
//! [`Pool`]s are created by calling [`Runtime::pkt_pool`].

use core::{
    ffi::{CStr, c_uint, c_void},
    fmt,
    marker::{PhantomData, PhantomPinned},
    mem::{self, ManuallyDrop, MaybeUninit},
    ops::{Deref, DerefMut, RangeBounds},
    ptr::{self, NonNull},
    slice,
};

use bstr::BStr;

use crate::{
    call, ffi,
    rt::Runtime,
    sys,
    util::{FmtFn, neg},
};

/// A pool of [`Segment`]s which may be joined to form [`Packet`]s.
#[repr(transparent)]
pub struct Pool<'rt, T = ()> {
    sys: NonNull<sys::rte_mempool>,
    rt: PhantomData<&'rt Runtime>,
    meta: PhantomData<T>,
}

impl Runtime {
    pub fn pkt_pool<'rt>(
        &'rt self,
        name: &CStr,
        capacity: c_uint,
        space: u16,
    ) -> ffi::Result<Pool<'rt>> {
        self.pkt_pool_of(name, capacity, space)
    }
    /// Create a new pool with space for `capacity` [`Segment`]s,
    /// each with `space` bytes of [`space`](Segment::space).
    ///
    /// Metadata `T` is [`Default`]ed in each [`Segment`].
    pub fn pkt_pool_of<'rt, T: Default>(
        &'rt self,
        name: &CStr,
        capacity: c_uint,
        space: u16,
    ) -> ffi::Result<Pool<'rt, T>> {
        Pool::new(self, name, capacity, space)
    }
}

impl<'rt, T> Pool<'rt, T> {
    fn new(rt: &'rt Runtime, name: &CStr, capacity: c_uint, space: u16) -> Result<Self, ffi::Error>
    where
        T: Default,
    {
        Self::with(rt, name, capacity, space, || T::default())
    }
    /// Like [`Runtime::pkt_pool`], but initialize metadata `T` with the given initializer `f`.
    pub fn with<F: FnMut() -> T>(
        rt: &'rt Runtime,
        name: &CStr,
        capacity: c_uint,
        space: u16,
        mut f: F,
    ) -> Result<Self, ffi::Error> {
        unsafe {
            Self::init(rt, name, capacity, space, |initme| {
                initme.write(f());
            })
        }
    }
    /// Like [`Runtime::pkt_pool`], but initialize metadata `T` with the given initializer `f`.
    ///
    /// # Safety
    /// - `f` must initialize its argument.
    pub unsafe fn init<F: FnMut(&mut MaybeUninit<T>)>(
        rt: &'rt Runtime,
        name: &CStr,
        capacity: c_uint,
        space: u16,
        mut f: F,
    ) -> Result<Self, ffi::Error> {
        unsafe extern "C-unwind" fn obj_cb<F, T>(
            _mp: *mut sys::rte_mempool,
            opaque: *mut c_void,
            obj: *mut c_void,
            _obj_idx: c_uint,
        ) where
            F: FnMut(&mut MaybeUninit<T>),
        {
            let m = obj as *mut Segment<MaybeUninit<T>>;
            unsafe { &mut *m }.space_mut().fill(0);
            let initme = unsafe { &mut *m }.meta_mut();
            let f = opaque as *mut F;
            (unsafe { &mut *f })(initme);
        }

        let _ = rt;

        const { assert!(mem::align_of::<T>() <= sys::RTE_MBUF_PRIV_ALIGN as usize) }
        let priv_size = const {
            let u = mem::size_of::<T>();
            assert!(c_uint::BITS <= usize::BITS);
            assert!(u < c_uint::MAX as _);
            u as _
        };
        let call;
        let sys = NonNull::new(call!(
            sys::rte_pktmbuf_pool_create(
                name.as_ptr(),
                capacity,
                0,
                priv_size,
                space,
                sys::SOCKET_ID_ANY
            ) in call
        ))
        .ok_or(ffi::Error(call))?;
        unsafe {
            sys::rte_mempool_obj_iter(
                sys.as_ptr(),
                Some(obj_cb::<F, T>),
                &mut f as *mut F as *mut c_void,
            )
        };
        Ok(unsafe { Self::from_raw(sys) })
    }

    /// Remove a single [`Segment`] from the pool.
    ///
    /// The segment will be logically empty, with no headroom, no space, and a full tailroom.
    pub fn pop_segment(&self) -> Option<FreeSegment<'_, T>> {
        let mut mbuf = ptr::null_mut();
        let call;
        match (
            call!(sys::rte_mempool_get(self.sys.as_ptr(), &mut mbuf) in call),
            NonNull::new(mbuf),
        ) {
            (0, Some(nn)) => Some({
                let mut seg = FreeSegment(nn.cast());
                seg.clear();
                seg
            }),
            (neg::ENOENT, None) => None,
            (neg::ENOBUFS, None) => None, // undocumented
            _ => panic!("bad return from {call}"),
        }
    }
    /// Allocate a [`Packet`] with `cap` total [`space`](Segment::space),
    /// possibly over multiple [`Segment`]s.
    pub fn get_pkt(&self, cap: u32) -> Option<Packet<'_, T>> {
        let seg = self.pop_segment()?;
        let n = usize::try_from(cap).unwrap().div_ceil(seg.space().len());
        let mut pkt = Packet::from(seg);
        for _ in 1..n {
            pkt.extend([self.pop_segment()?]);
        }
        debug_assert!(pkt.capacity() >= cap);
        Some(pkt)
    }
    /// Get the name this pool was created with in [`Runtime::pkt_pool`].
    pub fn name(&self) -> &BStr {
        let chars = unsafe { &self.sys.as_ref().name[..] };
        let bytes = unsafe { &*(chars as *const [i8] as *const [u8]) };
        match CStr::from_bytes_until_nul(bytes) {
            Ok(it) => BStr::new(it.to_bytes()),
            Err(_) => BStr::new(bytes),
        }
    }
    /// Get number of [`Segment`]s in use from this pool.
    ///
    /// This should only be used for debugging purposes.
    #[expect(clippy::len_without_is_empty)]
    pub fn len(&self) -> c_uint {
        unsafe { sys::rte_mempool_in_use_count(self.sys.as_ptr()) }
    }
    /// Get the maximum number of [`Segment`]s this pool can allocate.
    pub fn capacity(&self) -> c_uint {
        unsafe { self.sys.as_ref().size }
    }
    /// Get number of [`Segment`]s not in use from this pool.
    ///
    /// This should only be used for debugging purposes.
    pub fn spare_capacity(&self) -> c_uint {
        unsafe { sys::rte_mempool_avail_count(self.sys.as_ptr()) }
    }
    /// Get the raw underlying pointer for this pool.
    pub fn as_raw(&self) -> NonNull<sys::rte_mempool> {
        self.sys
    }
    pub fn into_raw(self) -> NonNull<sys::rte_mempool> {
        ManuallyDrop::new(self).sys
    }
    pub unsafe fn from_raw(sys: NonNull<sys::rte_mempool>) -> Self {
        Self {
            sys,
            rt: PhantomData,
            meta: PhantomData,
        }
    }
}

impl<T> fmt::Debug for Pool<'_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Pool")
            .field("name", &self.name())
            .field("len", &self.len())
            .field("capacity", &self.capacity())
            .finish_non_exhaustive()
    }
}

impl<T> Drop for Pool<'_, T> {
    fn drop(&mut self) {
        unsafe extern "C-unwind" fn drop<T>(
            _mp: *mut sys::rte_mempool,
            _arg: *mut c_void,
            obj: *mut c_void,
            _obj_idx: c_uint,
        ) {
            unsafe {
                ptr::drop_in_place(
                    Segment::<T>::mut_from_raw(NonNull::new(obj).unwrap().cast()).meta_mut(),
                )
            };
        }
        unsafe {
            if mem::needs_drop::<T>() {
                sys::rte_mempool_obj_iter(self.sys.as_ptr(), Some(drop::<T>), ptr::null_mut());
            }
            sys::rte_mempool_free(self.sys.as_ptr())
        }
    }
}

unsafe impl<T: Send> Send for Pool<'_, T> {}
unsafe impl<T: Sync> Sync for Pool<'_, T> {}

/// An owned, single [`Segment`].
pub struct FreeSegment<'pool, T = ()>(NonNull<Segment<'pool, T>>);

impl<T> FreeSegment<'_, T> {
    pub fn as_raw(&self) -> NonNull<sys::rte_mbuf> {
        unsafe { NonNull::new_unchecked(self.0.as_ref()._header()) }
    }
    pub fn into_raw(self) -> NonNull<sys::rte_mbuf> {
        ManuallyDrop::new(self).0.cast()
    }
    pub unsafe fn from_raw(ptr: NonNull<sys::rte_mbuf>) -> Self {
        Self(ptr.cast())
    }
}

impl<T: fmt::Debug> fmt::Debug for FreeSegment<'_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        Segment::fmt(self, f)
    }
}
impl<T> fmt::Pointer for FreeSegment<'_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt::Pointer::fmt(&self.0, f)
    }
}

impl<T> Drop for FreeSegment<'_, T> {
    fn drop(&mut self) {
        unsafe { sys::rte_pktmbuf_free(self._header()) }
    }
}

impl<'pool, T> Deref for FreeSegment<'pool, T> {
    type Target = Segment<'pool, T>;
    fn deref(&self) -> &Self::Target {
        unsafe { self.0.as_ref() }
    }
}

impl<T> DerefMut for FreeSegment<'_, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { self.0.as_mut() }
    }
}
unsafe impl<T> bytes::BufMut for FreeSegment<'_, T> {
    fn remaining_mut(&self) -> usize {
        Segment::remaining_mut(self)
    }
    unsafe fn advance_mut(&mut self, cnt: usize) {
        unsafe { Segment::advance_mut(self, cnt) }
    }
    fn chunk_mut(&mut self) -> &mut bytes::buf::UninitSlice {
        Segment::chunk_mut(self)
    }
}

impl<'pool, T> From<FreeSegment<'pool, T>> for Packet<'pool, T> {
    fn from(value: FreeSegment<'pool, T>) -> Self {
        let mut pkt = Packet {
            head: value.into_raw().cast(),
        };
        drop(pkt.iter_mut());
        pkt
    }
}

unsafe impl<T: Send> Send for FreeSegment<'_, T> {}
unsafe impl<T: Sync> Sync for FreeSegment<'_, T> {}

/// A non-empty, owned linked list of [`Segment`]s.
pub struct Packet<'pool, T = ()> {
    head: NonNull<Segment<'pool, T>>,
}

impl<'pool, T> Packet<'pool, T> {
    pub fn first(&self) -> &Segment<'_, T> {
        self.iter().next().unwrap()
    }
    pub fn first_mut(&mut self) -> &mut Segment<'pool, T> {
        self.iter_mut().next().unwrap()
    }
    pub fn last(&self) -> &Segment<'_, T> {
        self.iter().last().unwrap()
    }
    pub fn last_mut(&mut self) -> &mut Segment<'pool, T> {
        self.iter_mut().last().unwrap()
    }
    pub fn iter(&self) -> Iter<'_, 'pool, T> {
        Iter {
            raw: Raw::new(self.head),
            lt: PhantomData,
        }
    }
    pub fn iter_mut(&mut self) -> IterMut<'_, 'pool, T> {
        unsafe { IterMut::new(self.head) }
    }
    /// Get the total [`Segment::data`] over all segments in this packet.
    pub fn len(&self) -> u32 {
        unsafe { *sys::pktmbuf_pkt_len(self.head.as_ref()._header()) }
    }
    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }
    /// Get the total [`Segment::space`] over all segments in this packet.
    pub fn capacity(&self) -> u32 {
        self.iter()
            .map(|it| it.space().len())
            .sum::<usize>()
            .try_into()
            .unwrap()
    }
    pub fn linearized(self) -> Result<FreeSegment<'pool, T>, Self> {
        let call;
        match call!(sys::rte_pktmbuf_linearize(self.head.as_ref()._header()) in call) {
            0 => Ok(unsafe { FreeSegment::from_raw(ManuallyDrop::new(self).head.cast()) }),
            -1 => Err(self),
            _ => panic!("bad return code in {call}"),
        }
    }
    pub fn buf(&self) -> Buf<'_, 'pool, T> {
        Buf {
            off: 0,
            iter: self.iter(),
        }
    }
    pub fn buf_mut(&mut self) -> BufMut<'_, 'pool, T> {
        BufMut {
            iter: self.iter_mut(),
        }
    }
    pub fn as_raw(&self) -> NonNull<sys::rte_mbuf> {
        unsafe { NonNull::new_unchecked(self.head.as_ref()._header()) }
    }
    pub fn into_raw(self) -> NonNull<sys::rte_mbuf> {
        ManuallyDrop::new(self).head.cast()
    }
    pub unsafe fn from_raw(ptr: NonNull<sys::rte_mbuf>) -> Self {
        Self { head: ptr.cast() }
    }
}

impl<T: fmt::Debug> fmt::Debug for Packet<'_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_tuple("Packet")
            .field(&FmtFn::new(|f| {
                f.debug_list().entries(self.iter()).finish()
            }))
            .finish()
    }
}

impl<T> Drop for Packet<'_, T> {
    fn drop(&mut self) {
        unsafe { sys::rte_pktmbuf_free(self.first_mut()._header()) }
    }
}

impl<'pool, T> Extend<FreeSegment<'pool, T>> for Packet<'pool, T> {
    fn extend<II: IntoIterator<Item = FreeSegment<'pool, T>>>(&mut self, iter: II) {
        for seg in iter {
            let call;
            match call!(sys::rte_pktmbuf_chain(
                self.as_raw().as_ptr(),
                seg.into_raw().as_ptr()
            ) in call)
            {
                0 => {}
                neg::EOVERFLOW => panic!("segment count exceeded"),
                _ => panic!("bad rc in {call}"),
            }
        }
        drop(self.iter_mut());
    }
}

unsafe impl<T: Send> Send for Packet<'_, T> {}
unsafe impl<T: Sync> Sync for Packet<'_, T> {}

/// Implementor of [`bytes::Buf`] for a [`Packet`].
#[derive(Debug)]
pub struct Buf<'pkt, 'pool, T> {
    /// Offset into [`Iter::peek`]
    off: usize,
    iter: Iter<'pkt, 'pool, T>,
}

impl<T> Clone for Buf<'_, '_, T> {
    fn clone(&self) -> Self {
        Self {
            off: self.off,
            iter: self.iter.clone(),
        }
    }
}

impl<T> bytes::Buf for Buf<'_, '_, T> {
    fn remaining(&self) -> usize {
        self.iter
            .clone()
            .enumerate()
            .map(|(ix, seg)| match ix == 0 {
                true => seg.data()[self.off..].len(),
                false => seg.data().len(),
            })
            .sum()
    }
    fn chunk(&self) -> &[u8] {
        self.iter.peek().map(|it| it.data()).unwrap_or_default()
    }
    fn advance(&mut self, mut cnt: usize) {
        while let Some(peek) = self.iter.peek() {
            let buf = &peek.data()[self.off..];
            if cnt < buf.len() {
                self.off += cnt;
                break;
            } else {
                cnt -= buf.len();
                self.off = 0;
                self.iter.next();
            }
        }
    }
}

/// Implementor of [`bytes::BufMut`] for a [`Packet`].
#[derive(Debug)]
pub struct BufMut<'pkt, 'pool, T> {
    iter: IterMut<'pkt, 'pool, T>,
}

unsafe impl<T> bytes::BufMut for BufMut<'_, '_, T> {
    fn remaining_mut(&self) -> usize {
        self.iter.remaining().map(Segment::remaining_mut).sum()
    }

    unsafe fn advance_mut(&mut self, mut cnt: usize) {
        while let Some(peek) = self.iter.peek_mut() {
            if cnt < peek.remaining_mut() {
                unsafe { peek.advance_mut(cnt) };
                break;
            } else {
                cnt -= peek.remaining_mut();
                unsafe { peek.advance_mut(peek.remaining_mut()) };
                self.iter.next();
            }
        }
    }

    fn chunk_mut(&mut self) -> &mut bytes::buf::UninitSlice {
        while let Some(peek) = self.iter.peek_mut() {
            match peek.has_remaining_mut() {
                true => {
                    return unsafe {
                        let extend_lt = peek.chunk_mut() as *mut _;
                        &mut *extend_lt
                    };
                }
                false => drop(self.iter.next()),
            }
        }
        bytes::buf::UninitSlice::new(&mut [])
    }
}

struct Raw<'pool, T> {
    current: Option<NonNull<Segment<'pool, T>>>,
}
impl<T> Clone for Raw<'_, T> {
    fn clone(&self) -> Self {
        Self {
            current: self.current,
        }
    }
}

impl<'pool, T> Raw<'pool, T> {
    fn new(head: NonNull<Segment<'pool, T>>) -> Self {
        Self {
            current: Some(head),
        }
    }
}

impl<'pool, T> Iterator for Raw<'pool, T> {
    type Item = NonNull<Segment<'pool, T>>;
    fn next(&mut self) -> Option<Self::Item> {
        let yieldme = self.current?;
        self.current = NonNull::new(
            unsafe { yieldme.as_ref() }
                .header
                .next
                .cast::<Segment<'pool, T>>(),
        );
        Some(yieldme)
    }
}

/// Iterator of [`&Segment`](Segment).
pub struct Iter<'pkt, 'pool, T> {
    raw: Raw<'pool, T>,
    lt: PhantomData<&'pkt Packet<'pool, T>>,
}

impl<'pkt, 'pool, T> Iter<'pkt, 'pool, T> {
    pub fn peek(&self) -> Option<&'pkt Segment<'pool, T>> {
        self.clone().next()
    }
}

impl<T> Clone for Iter<'_, '_, T> {
    fn clone(&self) -> Self {
        Self {
            raw: self.raw.clone(),
            lt: PhantomData,
        }
    }
}

impl<T: fmt::Debug> fmt::Debug for Iter<'_, '_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_tuple("Iter")
            .field(&FmtFn::new(|f| {
                f.debug_list().entries(self.clone()).finish()
            }))
            .finish()
    }
}

impl<'pkt, 'pool, T> Iterator for Iter<'pkt, 'pool, T> {
    type Item = &'pkt Segment<'pool, T>;
    fn next(&mut self) -> Option<Self::Item> {
        Some(unsafe { self.raw.next()?.as_ref() })
    }
}

impl<T> itertools::PeekingNext for Iter<'_, '_, T> {
    fn peeking_next<F: FnOnce(&Self::Item) -> bool>(&mut self, accept: F) -> Option<Self::Item> {
        match accept(&self.clone().next()?) {
            true => self.next(),
            false => None,
        }
    }
}

impl<'pkt, 'pool, T> IntoIterator for &'pkt Packet<'pool, T> {
    type Item = &'pkt Segment<'pool, T>;
    type IntoIter = Iter<'pkt, 'pool, T>;
    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}

/// Iterator of [`&mut Segment`](Segment).
///
/// [`Packet::len`] is updated when the iterator is dropped.
pub struct IterMut<'pkt, 'pool, T> {
    head: NonNull<Segment<'pool, T>>,
    inner: Raw<'pool, T>,
    lt: PhantomData<&'pkt mut Packet<'pool, T>>,
}

impl<T: fmt::Debug> fmt::Debug for IterMut<'_, '_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_tuple("IterMut")
            .field(&FmtFn::new(|it| {
                it.debug_list().entries(self.remaining()).finish()
            }))
            .finish()
    }
}

impl<'pool, T> IterMut<'_, 'pool, T> {
    unsafe fn new(head: NonNull<Segment<'pool, T>>) -> Self {
        Self {
            head,
            inner: Raw::new(head),
            lt: PhantomData,
        }
    }
    pub fn remaining(&self) -> Iter<'_, 'pool, T> {
        Iter {
            raw: self.inner.clone(),
            lt: PhantomData,
        }
    }
    pub fn peek(&self) -> Option<&'_ Segment<'pool, T>> {
        Some(unsafe { self.inner.clone().next()?.as_ref() })
    }
    pub fn peek_mut(&mut self) -> Option<&'_ mut Segment<'pool, T>> {
        Some(unsafe { self.inner.clone().next()?.as_mut() })
    }
}

impl<'pkt, 'pool, T> Iterator for IterMut<'pkt, 'pool, T> {
    type Item = &'pkt mut Segment<'pool, T>;
    fn next(&mut self) -> Option<Self::Item> {
        Some(unsafe { self.inner.next()?.as_mut() })
    }
}

impl<T> itertools::PeekingNext for IterMut<'_, '_, T> {
    fn peeking_next<F: FnOnce(&Self::Item) -> bool>(&mut self, accept: F) -> Option<Self::Item> {
        match accept(&unsafe { self.inner.clone().next()?.as_mut() }) {
            true => self.next(),
            false => None,
        }
    }
}

impl<'pkt, 'pool, T> IntoIterator for &'pkt mut Packet<'pool, T> {
    type Item = &'pkt mut Segment<'pool, T>;
    type IntoIter = IterMut<'pkt, 'pool, T>;
    fn into_iter(self) -> Self::IntoIter {
        self.iter_mut()
    }
}

impl<T> Drop for IterMut<'_, '_, T> {
    fn drop(&mut self) {
        let mut len = 0;
        for seg in (Iter {
            raw: Raw::new(self.head),
            lt: PhantomData,
        }) {
            len += u32::from(unsafe { *sys::pktmbuf_data_len(seg._header()) });
        }
        unsafe { *sys::pktmbuf_pkt_len(self.head.as_mut()._header()) = len }
    }
}

/// A segment is a fixed-sized byte array, used to hold packet data.
///
/// There is a [`space`](Self::space), of which a subslice,
/// [`data`](Self::data) is logically initialized.
///
/// There is additionally per-segment metadata of type `T`.
/// The lifetime of this metadata is tied to the [`Pool`] that owns the [`Segment`].
///
/// This type is unconstructable, and is intended to only live behind a reference.
///
/// ```text
/// ┌─────────────────┬─────────┬────────────────────────────────────────┐
/// │     header      │ meta: T │              space: [u8]               │
/// │ : sys::rte_mbuf │         │                                        │
/// │                 │         │◄──headroom──►│◄──data──►│◄──tailroom──►│
/// └─────────────────┴─────────┴────────────────────────────────────────┘
/// ```
///
/// DPDK calls a [`Segment`] an `mbuf`.
#[repr(C)]
pub struct Segment<'pool, T = ()> {
    header: sys::rte_mbuf,
    meta: PhantomData<ManuallyDrop<T>>,
    life: PhantomData<&'pool ()>,
    _pinned: PhantomPinned,
    _space: c_void, // morally, this should be [u8], but constructing references
                    // to such a type is non-trivial
}

macro_rules! slices {
    ($($ref:ident / $mut:ident = $raw:ident);* $(;)?) => {
        $(
            pub fn $ref(&self) -> &[u8] {
                let (ptr, len) = self.$raw();
                unsafe { slice::from_raw_parts(ptr, len) }
            }
            pub fn $mut(&mut self) -> &mut [u8] {
                let (ptr, len) = self.$raw();
                unsafe { slice::from_raw_parts_mut(ptr, len) }
            }
        )*
    };
}

impl<T> Segment<'_, T> {
    pub const unsafe fn ref_from_raw<'a>(ptr: NonNull<sys::rte_mbuf>) -> &'a Self {
        unsafe { ptr.cast().as_ref() }
    }
    pub const unsafe fn mut_from_raw<'a>(ptr: NonNull<sys::rte_mbuf>) -> &'a mut Self {
        unsafe { ptr.cast().as_mut() }
    }

    slices! {
        data / data_mut = _data;
        space / space_mut = _space;
        tailroom / tailroom_mut = _tailroom;
        headroom / headroom_mut = _headroom;
    }
    pub fn meta(&self) -> &T {
        unsafe { &*self._meta() }
    }
    pub fn meta_mut(&mut self) -> &mut T {
        unsafe { &mut *self._meta() }
    }

    /// Set [`data`](Self::data) to be a subslice of [`space`](Self::space).
    ///
    /// # Panics
    /// - if `range` is out-of-bounds for `space`.
    pub fn set_data<R: RangeBounds<usize>>(&mut self, range: R) {
        let space = self.space();
        let space_addr = space.as_ptr();
        let data = &space[(range.start_bound().cloned(), range.end_bound().cloned())];
        let data_addr = data.as_ptr();
        let data_off = u16::try_from(unsafe { data_addr.offset_from(space_addr) })
            .expect("space len fits in u16");
        let len = u16::try_from(data.len()).expect("space len fits in u16");
        self.header.__bindgen_anon_1.__bindgen_anon_1.data_off = data_off;
        unsafe { *sys::pktmbuf_data_len(self._header()) = len };
    }

    pub fn clear(&mut self) {
        self.set_data(..0);
    }

    pub fn parts_mut(&mut self) -> (&mut [u8], &mut [u8], &mut [u8]) {
        let head = self.headroom_mut() as *mut _;
        let data = self.data_mut() as *mut _;
        let tail = self.tailroom_mut() as *mut _;
        unsafe { (&mut *head, &mut *data, &mut *tail) }
    }

    fn _meta(&self) -> *mut T {
        const { assert!(mem::align_of::<T>() <= sys::RTE_MBUF_PRIV_ALIGN as usize) }
        let ptr = unsafe { sys::rte_mbuf_to_priv(self._header()) as *mut T };
        debug_assert!(ptr.is_aligned());
        ptr
    }
    fn _space(&self) -> (*mut u8, usize) {
        unsafe {
            (
                self.header.buf_addr as *mut u8,
                usize::from(self.header.__bindgen_anon_2.__bindgen_anon_1.buf_len),
            )
        }
    }
    fn _headroom(&self) -> (*mut u8, usize) {
        let (ptr, _) = self._space();
        (
            ptr,
            usize::from(unsafe { sys::rte_pktmbuf_headroom(&self.header) }),
        )
    }
    fn _data(&self) -> (*mut u8, usize) {
        unsafe {
            (
                sys::rte_pktmbuf_mtod(self._header()) as *mut u8,
                usize::from(*sys::pktmbuf_data_len(self._header())),
            )
        }
    }
    fn _tailroom(&self) -> (*mut u8, usize) {
        (
            self.data().as_ptr_range().end as *mut u8,
            usize::from(unsafe { sys::rte_pktmbuf_tailroom(self._header()) }),
        )
    }
    /// bindgen'ed functions take `*mut rte_mbuf`.
    fn _header(&self) -> *mut sys::rte_mbuf {
        &self.header as *const sys::rte_mbuf as *mut sys::rte_mbuf
    }
}

impl<T: fmt::Debug> fmt::Debug for Segment<'_, T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Segment")
            .field("meta", &self.meta())
            .field("headroom", &self.headroom())
            .field("data", &self.data())
            .field("tailroom", &self.tailroom())
            .finish_non_exhaustive()
    }
}

unsafe impl<T> bytes::BufMut for Segment<'_, T> {
    fn remaining_mut(&self) -> usize {
        self.tailroom().len()
    }
    unsafe fn advance_mut(&mut self, cnt: usize) {
        #[cfg(debug_assertions)]
        let tailroom = self.tailroom().len();
        self.set_data(self.headroom().len()..(self.headroom().len() + self.data().len() + cnt));
        debug_assert_eq!(self.tailroom().len(), tailroom - cnt);
    }
    fn chunk_mut(&mut self) -> &mut bytes::buf::UninitSlice {
        self.tailroom_mut().into()
    }
}

#[cfg(test)]
mod tests {
    use std::{
        io::{self, Write as _},
        vec::Vec,
    };

    use bytes::{Buf, BufMut};

    use super::*;

    #[test]
    fn pool_caps() {
        let pool = &crate::rt::test()
            .pkt_pool_of::<()>(c"pool_caps", 2, 6)
            .unwrap();
        assert(pool, 2, 0, 2);
        let s1 = pool.pop_segment().unwrap();
        assert(pool, 2, 1, 1);
        let s2 = pool.pop_segment().unwrap();
        assert(pool, 2, 2, 0);
        unwrap_none(pool.pop_segment());
        drop(s2);
        assert(pool, 2, 1, 1);
        pool.pop_segment().unwrap();
        drop(s1);
        assert(pool, 2, 0, 2);
    }

    #[test]
    fn seg_buf() {
        let pool = &crate::rt::test()
            .pkt_pool_of::<()>(c"seg_buf", 1, 5)
            .unwrap();
        let mut seg = pool.pop_segment().unwrap();
        assert_eq!(seg.data(), []);
        (&mut seg).writer().write_all(b"hello").unwrap();
        assert_eq!(seg.data(), b"hello");
        seg.clear();
        assert_eq!(seg.data(), []);
    }

    #[test]
    fn pkt_buf() {
        let pool = &crate::rt::test()
            .pkt_pool_of::<()>(c"pkt_buf", 2, 4)
            .unwrap();
        let mut pkt = pool.get_pkt(6).unwrap();
        assert_eq!(pkt.capacity(), 8);
        assert_eq!(pkt.len(), 0);
        assert_eq!(read_to_end(pkt.buf().reader()), []);
        pkt.buf_mut().writer().write_all(b"hello").unwrap();
        assert_eq!(read_to_end(pkt.buf().reader()), b"hello");
        assert_eq!(pkt.iter().map(|it| it.data().len()).sum::<usize>(), 5);
        assert_eq!(pkt.len(), 5);
    }

    #[test]
    fn linearize() {
        let pool = &crate::rt::test()
            .pkt_pool_of::<()>(c"linearize", 2, 5)
            .unwrap();
        let mut seg1 = pool.pop_segment().unwrap();
        seg1.put_slice(b"hel");
        let mut seg2 = pool.pop_segment().unwrap();
        seg2.put_slice(b"lo");
        let mut pkt = Packet::from(seg1);
        pkt.extend([seg2]);
        assert_eq!(pkt.iter().count(), 2);
        let seg = pkt.linearized().unwrap();
        assert_eq!(seg.data(), b"hello")
    }

    #[track_caller]
    fn read_to_end<R: io::Read>(mut r: R) -> Vec<u8> {
        let mut v = Vec::new();
        r.read_to_end(&mut v).unwrap();
        v
    }

    #[track_caller]
    fn assert<T>(pool: &Pool<'_, T>, cap: c_uint, len: c_uint, sp: c_uint) {
        assert_eq!(pool.capacity(), cap);
        assert_eq!(pool.len(), len);
        assert_eq!(pool.spare_capacity(), sp);
    }

    #[track_caller]
    fn unwrap_none<T: fmt::Debug>(it: Option<T>) {
        if let Some(it) = it {
            panic!("called `unwrap_none` on a `Some` value: {it:?}")
        }
    }
}
