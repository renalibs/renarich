#ifndef __RENALIBS_RENARICH_BUILTIN_NWSTRCVT_H__
#define __RENALIBS_RENARICH_BUILTIN_NWSTRCVT_H__

#include<string>

namespace rena::builtin {

    std::wstring nwstrcvt_to_wstr( const std::string& __c_s_str , bool __b_force_utf_8 = false );
    std::string nwstrcvt_to_nstr( const std::wstring& __c_ws_str , bool __b_force_utf_8 = false );

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_NWSTRCVT_H__
