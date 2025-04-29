use core::{
    cell::RefCell,
    fmt::{self, Write as _},
};

use crate::{sys, util::SeeString};

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u32)]
pub enum Level {
    Emerg = sys::RTE_LOG_EMERG,
    Alert = sys::RTE_LOG_ALERT,
    Crit = sys::RTE_LOG_CRIT,
    Err = sys::RTE_LOG_ERR,
    Warning = sys::RTE_LOG_WARNING,
    Notice = sys::RTE_LOG_NOTICE,
    Info = sys::RTE_LOG_INFO,
    Debug = sys::RTE_LOG_DEBUG,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord, Hash)]
#[repr(u32)]
pub enum Type {
    User1 = sys::RTE_LOGTYPE_USER1,
    User2 = sys::RTE_LOGTYPE_USER2,
    User3 = sys::RTE_LOGTYPE_USER3,
    User4 = sys::RTE_LOGTYPE_USER4,
    User5 = sys::RTE_LOGTYPE_USER5,
    User6 = sys::RTE_LOGTYPE_USER6,
    User7 = sys::RTE_LOGTYPE_USER7,
    User8 = sys::RTE_LOGTYPE_USER8,
}

#[inline]
pub fn log(loglevel: Level, logtype: Type, args: fmt::Arguments<'_>) {
    std::thread_local! {
        static BUF: RefCell<SeeString> = const { RefCell::new(SeeString::new()) };
    }
    if !unsafe { sys::rte_log_can_log(logtype as u32, loglevel as u32) } {
        return;
    }
    BUF.with_borrow_mut(|buf| {
        let prefix = match logtype {
            Type::User1 => "USER1",
            Type::User2 => "USER2",
            Type::User3 => "USER3",
            Type::User4 => "USER4",
            Type::User5 => "USER5",
            Type::User6 => "USER6",
            Type::User7 => "USER7",
            Type::User8 => "USER8",
        };
        buf.clear();
        match buf.write_fmt(format_args!("{prefix}: {args}")) {
            Ok(()) => unsafe {
                if sys::rte_log(
                    loglevel as u32,
                    logtype as u32,
                    c"%s\n".as_ptr(),
                    buf.as_cstr(),
                )
                .is_negative()
                {
                    let _ = sys::rte_log(
                        Level::Err as u32,
                        Type::User1 as u32,
                        c"DEEPEEDEEKAY: logging error\n".as_ptr(),
                    );
                }
            },
            Err(fmt::Error) => unsafe {
                let _ = sys::rte_log(
                    Level::Err as u32,
                    Type::User1 as u32,
                    c"DEEPEEDEEKAY: oom for logging\n".as_ptr(),
                );
            },
        }
    });
}
