#include"rena/renarichxx.h"
#include"rena/renarich_errcodes.h"
#include"rena/renarich_exceptions.h"

#include"builtin/box_chars.h"
#include"builtin/terminal_helper.h"
#include"builtin/wcwidth.h"

template<class _CharT>
std::basic_string<_CharT> rena::basic_panel<_CharT>::content() const noexcept {
    return this -> _s_content;
}

template<class _CharT>
void rena::basic_panel<_CharT>::content( const std::basic_string<_CharT>& __c_s_content ){
    this -> _s_content = __c_s_content;
    return;
}

template<class _CharT>
rena::color_code rena::basic_panel<_CharT>::frame_color() const noexcept {
    return this -> _cc_frame_color;
}

template<class _CharT>
void rena::basic_panel<_CharT>::frame_color( const rena::color_code& __c_cc_code ){
    if ( __c_cc_code._u8i_type != builtin::ColorCodeTypeForegroundColor )
    {
        throw exceptions::renarich_illegal_value( RENA_ERR_ILLEGAL_COLOR_CODE , "a foreground color is required" );
    }
    this -> _cc_frame_color = __c_cc_code;
    return;
}

template<class _CharT>
int rena::basic_panel<_CharT>::style() const noexcept {
    return this -> _i_style;
}

template<class _CharT>
void rena::basic_panel<_CharT>::style( int __i_style ){
    this -> _i_style = __i_style;
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::_render( std::basic_ostream<_CharT>& __os ) const {

    // builtin::coord terminal_size = builtin::get_terminal_size();
    int content_width = this -> _get_content_width();

    __os << this -> _get_space_char()
         << this -> _get_frame_char( BC_DR );
    for ( int i = 0 ; i < content_width + 2 ; i++ )
    {
        __os << this -> _get_frame_char( BC_H );
    }
    __os << this -> _get_frame_char( BC_DL )
         << std::endl
         << this -> _get_space_char()
         << this -> _get_frame_char( BC_V )
         << this -> _get_space_char() << this -> _s_content << this -> _get_space_char()
         << this -> _get_frame_char( BC_V )
         << std::endl
         << this -> _get_space_char()
         << this -> _get_frame_char( BC_UR );
    for ( int i = 0 ; i < content_width + 2 ; i++ )
    {
        __os << this -> _get_frame_char( BC_H );
    }
    __os << this -> _get_frame_char( BC_UL )
         << std::endl;
    
    return;
}

template class rena::basic_panel<char>;
template class rena::basic_panel<wchar_t>;

int rena::panel::_get_content_width() const {
    return builtin::swidth( this -> _s_content );
}

int rena::panel::_get_content_width( const std::string& __c_s_content ) const {
    return builtin::swidth( __c_s_content );
}

char rena::panel::_get_space_char() const noexcept {
    return ' ';
}

const std::string& rena::panel::_get_frame_char( int __i_c ) const {
    if ( !( __i_c >= 0 && __i_c < 11 ) )
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_table index overflow" );
    }

    if ( ( this -> _i_style & s_frame_single_line ) == s_frame_single_line )
    {
        return builtin::bc_table[BC_G_SLL][__i_c];
    }
    else if ( ( this -> _i_style & s_frame_double_line ) == s_frame_double_line )
    {
        return builtin::bc_table[BC_G_DLL][__i_c];
    }
    else if ( ( this -> _i_style & s_frame_rounded ) == s_frame_rounded )
    {
        return builtin::bc_table[BC_G_RLL][__i_c];
    }
    else if ( ( this -> _i_style & s_frame_heavy_single_line ) == s_frame_heavy_single_line )
    {
        return builtin::bc_table[BC_G_SLH][__i_c];
    }
    else
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_g not found" );
    }
}
