#ifndef __RENALIBS_RENARICH_BUILTIN_NWRPRINTF_H__
#define __RENALIBS_RENARICH_BUILTIN_NWRPRINTF_H__

#include<ostream>
#include<string>

namespace rena::builtin {

    template<class _CharT>
    int nwrprintf( const std::basic_string<_CharT>& __c_s_str , std::basic_ostream<_CharT>& __os , bool __b_style_reset = true );

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_NWRPRINTF_H__
