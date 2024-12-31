/**
 * This file is auto-generated by `src/tools/update_box_chars.py`
 * 
 * DO NOT EDIT!!!
 * 
 * If something is wrong, please fix it in `src/tools/templates/update_box_chars/box_chars.h.in` first
 */

#ifndef __RENALIBS_RENARICH_BUILTIN_BOX_CHARS_H__
#define __RENALIBS_RENARICH_BUILTIN_BOX_CHARS_H__

#include<string>

#define BC_H   0  // HORIZONTAL
#define BC_V   1  // VERTICAL
#define BC_DR  2  // DOWN AND RIGHT (Top Left Corner)
#define BC_DL  3  // DOWN AND LEFT (Top Right Corner)
#define BC_UR  4  // UP AND RIGHT (Bottom Left Corner)
#define BC_UL  5  // UP AND LEFT (Bottom Right Corner)
#define BC_VR  6  // VERTICAL AND RIGHT
#define BC_VL  7  // VERTICAL AND LEFT
#define BC_DH  8  // DOWN AND HORIZONTAL
#define BC_UH  9  // UNDER AND HORIZONTAL
#define BC_VH 10  // VERTICAL AND HORIZONTAL

#define BC_G_SLL 0
#define BC_G_SLH 1
#define BC_G_DLL 2
#define BC_G_RLL 3

namespace rena::builtin {

    extern const std::string bc_table[4][11];

    extern const std::wstring bc_w_table[4][11];

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_BOX_CHARS_H__
