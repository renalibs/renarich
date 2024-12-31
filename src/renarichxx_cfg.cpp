#include"rena/renarichxx.h"

bool rena::renarichxx_cfg::_b_force_utf8_codecvt = true;
bool rena::renarichxx_cfg::_b_use_cjk_char_spacing = false;

bool rena::renarichxx_cfg::force_utf8_codecvt(){
    return _b_force_utf8_codecvt;
}

void rena::renarichxx_cfg::force_utf8_codecvt( bool __b_enable ){
    _b_force_utf8_codecvt = __b_enable;
    return;
}

bool rena::renarichxx_cfg::use_cjk_char_spacing(){
    return _b_use_cjk_char_spacing;
}

void rena::renarichxx_cfg::use_cjk_char_spacing( bool __b_enable ){
    _b_use_cjk_char_spacing = __b_enable;
    return;
}
