#ifndef __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__
#define __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__

#include<string>

#include"rena/renarich.h"

namespace rena::builtin {

    bool is_legal_color_tag( const std::string& __c_s_tag );
    _color_code parse_color_tag( const std::string& __c_s_tag );

    constexpr _color_code PopColorTag = { 0x7F , 0x7F , 0x7F };
    constexpr _color_code PopAllColorTag = { 0x8F , 0x8F , 0x8F };
    constexpr _color_code IllegalColorTag = { 0xFF , 0xFF , 0xFF };

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_COLOR_TAG_H__
