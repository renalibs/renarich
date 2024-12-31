#include"rena/renarichxx.h"

#include<regex>
#include<sstream>
#include<string>

#include"builtin/color_tag.h"

template<class _CharT>
std::basic_string<_CharT> rena::basic_rcc<_CharT>::_get_content_without_color_tag( const std::basic_string<_CharT>& __c_s_str ){
    using _string = std::basic_string<_CharT>;
    using _string_const_iterator = typename _string::const_iterator;

    constexpr bool is_wchar_mode = ( std::is_same_v<_CharT,wchar_t> );

    std::basic_regex<_CharT> rbranket;
    if constexpr ( is_wchar_mode )
    {
        rbranket = std::basic_regex<_CharT>( LR"(\[(.*?)\])" );
    }
    else
    {
        rbranket = std::basic_regex<_CharT>( R"(\[(.*?)\])" );
    }

    std::regex_iterator<_string_const_iterator> rit( __c_s_str.begin() , __c_s_str.end() , rbranket );
    std::regex_iterator<_string_const_iterator> rend;
    std::basic_ostringstream<_CharT> oss;

    std::size_t lpos = 0;
    while ( rit != rend )
    {
        std::match_results<_string_const_iterator> match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_s_str[bpos-1] != '\\' ) )
        {
            _string tag_str = match[1].str();
            std::basic_stringstream<_CharT> ss( tag_str );
            _string this_tag;
            if constexpr ( is_wchar_mode )
            {
                while ( std::getline( ss , this_tag , L',' ) )
                {
                    rena::color_code this_code = rena::builtin::parse_color_tag( this_tag );
                    if ( this_code == rena::builtin::IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                }
            } // wchar
            else
            {
                while ( std::getline( ss , this_tag , ',' ) )
                {
                    rena::color_code this_code = rena::builtin::parse_color_tag( this_tag );
                    if ( this_code == rena::builtin::IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                }
            } // char
            oss << __c_s_str.substr( lpos , bpos - lpos );
            lpos = epos;
        }
next_iterator:
        ++rit;
    }
    if ( lpos < __c_s_str.size() )
    {
        oss << __c_s_str.substr( lpos );
    }
    
    return oss.str();
}

template class rena::basic_rcc<char>;
template class rena::basic_rcc<wchar_t>;
