#ifndef __RENALIBS_RENARICH_BUILTIN_WCWIDTH_H__
#define __RENALIBS_RENARICH_BUILTIN_WCWIDTH_H__

#include<cstddef>
#include<string>

namespace rena::builtin {

    int wcwidth( wchar_t __wc_c );
    int wcswidth( const wchar_t* __cp_wc_ws , std::size_t __ull_n );
    
    int swidth( const std::string& __c_s_str );
    int wswidth( const std::wstring& __c_ws_str );

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_WCWIDTH_H__
