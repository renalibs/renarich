#include"rena/renarichxx.h"

#include"builtin/nwrprintf.h"

template<class _CharT>
void rena::basic_rstring<_CharT>::_render( std::basic_ostream<_CharT>& __os ) const {
    auto lines = this -> _spilt_line_to_lines( *this );
    bool first_line = true;
    for ( const auto& it : lines )
    {
        if ( !first_line )
        {
            __os << std::endl;
        }
        else
        {
            first_line = false;
        }
        builtin::nwrprintf( it , __os );
    }
    return;
}

template class rena::basic_rstring<char>;
template class rena::basic_rstring<wchar_t>;
