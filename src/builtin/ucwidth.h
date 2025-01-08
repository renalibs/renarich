#ifndef __RENALIBS_RENARICH_BUILTIN_UCWIDTH_H__
#define __RENALIBS_RENARICH_BUILTIN_UCWIDTH_H__

#ifndef RENARICH_USE_ICU
#error "This header cannot be included when `RENARICH_USE_ICU` flag has been set to `OFF`"
#endif // RENARICH_USE_ICU

#include"unicode/unistr.h"

namespace rena::builtin {

    int ucwidth( UChar32 __c32_uc );
    int uswidth( const icu::UnicodeString& __c_us_str );

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_UCWIDTH_H__
