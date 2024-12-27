#include"rena/renarichxx.h"
#include"rena/renarich_errcodes.h"
#include"rena/renarich_exceptions.h"

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
void rena::basic_panel<_CharT>::_render( std::basic_ostream<_CharT>& __os ) const {
    // builtin::coord terminal_size = builtin::get_terminal_size();
    int content_width = this -> _get_content_width();

    __os << this -> _get_space_char()
         << this -> _get_frame_char( tlc );
    for ( int i = 0 ; i < content_width + 2 ; i++ )
    {
        __os << this -> _get_frame_char( tbl );
    }
    __os << this -> _get_frame_char( trc )
         << std::endl
         << this -> _get_space_char()
         << this -> _get_frame_char( lrv )
         << this -> _get_space_char() << this -> _s_content << this -> _get_space_char()
         << this -> _get_frame_char( lrv )
         << std::endl
         << this -> _get_space_char()
         << this -> _get_frame_char( blc );
    for ( int i = 0 ; i < content_width + 2 ; i++ )
    {
        __os << this -> _get_frame_char( tbl );
    }
    __os << this -> _get_frame_char( brc )
         << std::endl;
    
    return;
}

int rena::panel::_get_content_width() const {
    return builtin::swidth( this -> _s_content );
}

int rena::panel::_get_content_width( const std::string& __c_s_content ) const {
    return builtin::swidth( __c_s_content );
}

char rena::panel::_get_space_char() const noexcept {
    return ' ';
}

std::string rena::panel::_get_frame_char( rena::panel::_fc __c ) const {
    switch ( __c ) {
        case panel::tlc: return "┌";
        case panel::trc: return "┐";
        case panel::blc: return "└";
        case panel::brc: return "┘";
        case panel::tbl: return "─";
        case panel::lrv: return "│";
        default:
            throw exceptions::renarich_unexpected( RENA_ERR_UNEXPECTED , "unexcepted rena::panel::_fc value" );
    }
}
