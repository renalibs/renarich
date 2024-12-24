#ifndef __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__
#define __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__

#include<string>

#include"rena/renarich.h"

namespace rena::builtin {

    _color_code parse_color_tag( const std::string& __c_s_tag );

    constexpr _color_code PopColorTag = { 0x7f , 0x7f , 0x7f };
    constexpr _color_code IllegalColorTag = { 0xff , 0xff , 0xff };

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__
