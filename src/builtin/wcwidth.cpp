#include"wcwidth.h"

#include"builtin/ucwidth.h"

int rena::builtin::wcwidth( wchar_t __wc_c ){
#ifdef _WIN32
    return ucwidth( static_cast<UChar>( __wc_c ) );
#else // _WIN32
    return ucwidth( static_cast<UChar32>( __wc_c ) );
#endif // _WIN32
}

int rena::builtin::wcswidth( const wchar_t* __cp_wc_ws , std::size_t __ull_n ){
    int width = 0;
    for ( ; *__cp_wc_ws && __ull_n-- > 0 ; __cp_wc_ws++ )
    {
        width += wcwidth( *__cp_wc_ws );
    }
    return width;
}

int rena::builtin::swidth( const std::string& __c_s_str ){
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF8( __c_s_str );
    return uswidth( ustr );
}

int rena::builtin::wswidth( const std::wstring& __c_ws_str ){
#ifdef _WIN32
    icu::UnicodeString ustr = __c_ws_str;
#else // _WIN32
    icu::UnicodeString ustr = icu::UnicodeString::fromUTF32( reinterpret_cast<const UChar32*>( __c_ws_str.c_str() ) , __c_ws_str.size() );
#endif // _WIN32
    return uswidth( ustr );
}
