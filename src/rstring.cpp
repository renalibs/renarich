#include"rena/renarichxx.h"

#include"builtin/nwrprintf.h"

template<class _CharT>
void rena::basic_rstring<_CharT>::_render( std::basic_ostream<_CharT>& __os ) const {
    builtin::nwrprintf( *this , __os );
    return;
}

template class rena::basic_rstring<char>;
template class rena::basic_rstring<wchar_t>;
