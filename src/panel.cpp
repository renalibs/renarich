#include"rena/renarichxx.h"
#include"rena/renarich_errcodes.h"
#include"rena/renarich_exceptions.h"

#include<algorithm>
#include<bitset>

#include"builtin/box_chars.h"
#include"builtin/nwrprintf.h"
#include"builtin/wcwidth.h"

template<class _CharT>
std::vector<std::basic_string<_CharT>> rena::basic_panel<_CharT>::content() const noexcept {
    return this -> _vs_content;
}

template<class _CharT>
void rena::basic_panel<_CharT>::content( const std::vector<std::basic_string<_CharT>>& __c_vs_content ){
    this -> _vs_content = __c_vs_content;
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::push_line( const std::basic_string<_CharT>& __c_s_line ){
    this -> _vs_content.push_back( __c_s_line );
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::insert_line( const std::basic_string<_CharT>& __c_s_line , std::size_t __ull_pos ){
    if ( __ull_pos >= this -> _vs_content.size() )
    {
        throw exceptions::renarich_illegal_value( RENA_ERR_INDEX_OUT_OF_RANGE , "position out of range" );
    }
    this -> _vs_content.insert( this -> _vs_content.begin() + __ull_pos , __c_s_line );
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::pop_line(){
    this -> _vs_content.pop_back();
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::erase_line( std::size_t __ull_pos ){
    if ( __ull_pos >= this -> _vs_content.size() )
    {
        throw exceptions::renarich_illegal_value( RENA_ERR_INDEX_OUT_OF_RANGE , "position out of range" );
    }
    this -> _vs_content.erase( this -> _vs_content.begin() + __ull_pos );
    return;
}

template<class _CharT>
std::basic_string<_CharT> rena::basic_panel<_CharT>::title() const noexcept {
    return this -> _s_title;
}

template<class _CharT>
void rena::basic_panel<_CharT>::title( const std::basic_string<_CharT>& __c_s_title ){
    this -> _s_title = __c_s_title;
    return;
}

template<class _CharT>
std::basic_string<_CharT> rena::basic_panel<_CharT>::subtitle() const noexcept {
    return this -> _s_subtitle;
}

template<class _CharT>
void rena::basic_panel<_CharT>::subtitle( const std::basic_string<_CharT>& __c_s_subtitle ){
    this -> _s_subtitle = __c_s_subtitle;
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
unsigned int rena::basic_panel<_CharT>::style() const noexcept {
    return this -> _ui_style;
}

template<class _CharT>
void rena::basic_panel<_CharT>::style( unsigned int __ui_style ){
    std::bitset<12> style_bs( __ui_style );
    std::bitset<12> style_orig_bs( this -> _ui_style );

    if ( ( ( style_bs[0] + style_bs[1] ) == 0 ) )
    {
        style_bs[0] = style_orig_bs[0];
        style_bs[1] = style_orig_bs[1];
    } // title style not updated
    if ( ( style_bs[4] + style_bs[5] ) == 0 )
    {
        style_bs[4] = style_orig_bs[4];
        style_bs[5] = style_orig_bs[5];
    } // subtitle style not updated
    if ( ( style_bs[8] + style_bs[9] + style_bs[10] + style_bs[11] ) == 0 )
    {
        style_bs[8] = style_orig_bs[8];
        style_bs[9] = style_orig_bs[9];
        style_bs[10] = style_orig_bs[10];
        style_bs[11] = style_orig_bs[11];
    } // frame style not updated
    if ( ( ( style_bs[0] + style_bs[1] ) != 1 ) ||
         ( ( style_bs[2] + style_bs[3] ) != 0 ) ||
         ( ( style_bs[4] + style_bs[5] ) != 1 ) ||
         ( ( style_bs[6] + style_bs[7] ) != 0 ) ||
         ( ( style_bs[8] + style_bs[9] + style_bs[10] + style_bs[11] ) != 1 ) )
    {
        throw exceptions::renarich_illegal_value( RENA_ERR_ILLEGAL_STYLE , "illegal style code" );
    }

    this -> _ui_style = style_bs.to_ulong();
    return;
}

template<class _CharT>
void rena::basic_panel<_CharT>::_render( std::basic_ostream<_CharT>& __os ) const {
    int width = 0;
    std::vector<int> lines_width;
    for ( const auto& it : this -> _vs_content )
    {
        int this_line_width = this -> _get_content_width( it );
        width = std::max( width , this_line_width );
        lines_width.push_back( this_line_width );
    }
    int title_width = ( ( this -> _ui_style & s_title ) == s_title ) ? this -> _get_content_width( this -> _s_title ) + 2 : 0;
    int subtitle_width = ( ( this -> _ui_style & s_subtitle ) == s_subtitle ) ? this -> _get_content_width( this -> _s_subtitle ) + 2 : 0;
    width = std::max( { width , title_width , subtitle_width } );
    // panel width

    __os << this -> _get_space_char() << this -> _cc_frame_color
         << this -> _get_frame_char( BC_DR );
    if ( title_width == 0 )
    {
        for ( int i = 0 ; i < width + 2 ; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
    } // s_no_title
    else
    {
        for ( int i = 0 ; i < ( ( width - title_width ) / 2 ) + 1 ; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
        __os << rich_reset << this -> _get_space_char();
        builtin::nwrprintf( this -> _s_title , __os );
        __os << this -> _get_space_char() << this -> _cc_frame_color;
        for ( int i = 0 ; i < ( ( width - title_width ) / 2 + ( ( ( width - title_width ) % 2 == 0 ) ? 0 : 1 ) ) + 1; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
    } // s_title
    __os << this -> _get_frame_char( BC_DL )
         << rich_reset << std::endl;
    // title line

    for ( int l = 0 ; l < this -> _vs_content.size() ; l++ )
    {
        __os << this -> _get_space_char() << this -> _cc_frame_color
             << this -> _get_frame_char( BC_V ) << this -> _get_space_char()
             << rich_reset;
        builtin::nwrprintf( this -> _vs_content[l] , __os );
        __os << std::basic_string<_CharT>( width - lines_width[l] + 1 , this -> _get_space_char() )
             << this -> _cc_frame_color
             << this -> _get_frame_char( BC_V )
             << rich_reset << std::endl;
    }
    // lines

    __os << this -> _get_space_char() << this -> _cc_frame_color
         << this -> _get_frame_char( BC_UR );
    if ( subtitle_width == 0 )
    {
        for ( int i = 0 ; i < width + 2 ; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
    } // s_no_subtitle
    else
    {
        for ( int i = 0 ; i < ( width - subtitle_width ) / 2 + 1 ; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
        __os << rich_reset << this -> _get_space_char();
        builtin::nwrprintf( this -> _s_subtitle , __os );
        __os << this -> _get_space_char() << this -> _cc_frame_color;
        for ( int i = 0 ; i < ( ( width - subtitle_width ) / 2 + ( ( ( width - subtitle_width ) % 2 == 0 ) ? 0 : 1 ) ) + 1 ; i++ )
        {
            __os << this -> _get_frame_char( BC_H );
        }
    } // s_subtitle
    __os << this -> _get_frame_char( BC_UL )
         << rich_reset << std::endl;
    // subtitle line

    return;
}

template class rena::basic_panel<char>;
template class rena::basic_panel<wchar_t>;

int rena::panel::_get_content_width( const std::string& __c_s_content ) const {
    return builtin::swidth( this -> _get_content_without_color_tag( __c_s_content ) );
}

char rena::panel::_get_space_char() const noexcept {
    return ' ';
}

const std::string& rena::panel::_get_frame_char( int __i_c ) const {
    if ( !( __i_c >= 0 && __i_c < 11 ) )
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_table index overflow" );
    }

    if ( ( this -> _ui_style & s_frame_single_line ) == s_frame_single_line )
    {
        return builtin::bc_table[BC_G_SLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_double_line ) == s_frame_double_line )
    {
        return builtin::bc_table[BC_G_DLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_rounded ) == s_frame_rounded )
    {
        return builtin::bc_table[BC_G_RLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_heavy_single_line ) == s_frame_heavy_single_line )
    {
        return builtin::bc_table[BC_G_SLH][__i_c];
    }
    else
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_g not found" );
    }
}

int rena::wpanel::_get_content_width( const std::wstring& __c_ws_content ) const {
    return builtin::wswidth( this -> _get_content_without_color_tag( __c_ws_content ) );
}

wchar_t rena::wpanel::_get_space_char() const noexcept {
    return L' ';
}

const std::wstring& rena::wpanel::_get_frame_char( int __i_c ) const {
    if ( !( __i_c >= 0 && __i_c < 11 ) )
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_table index overflow" );
    }

    if ( ( this -> _ui_style & s_frame_single_line ) == s_frame_single_line )
    {
        return builtin::bc_w_table[BC_G_SLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_double_line ) == s_frame_double_line )
    {
        return builtin::bc_w_table[BC_G_DLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_rounded ) == s_frame_rounded )
    {
        return builtin::bc_w_table[BC_G_RLL][__i_c];
    }
    else if ( ( this -> _ui_style & s_frame_heavy_single_line ) == s_frame_heavy_single_line )
    {
        return builtin::bc_w_table[BC_G_SLH][__i_c];
    }
    else
    {
        throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "bc_g not found" );
    }
}
