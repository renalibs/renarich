#include"nwrprintf.h"

#include<regex>
#include<sstream>

#include"builtin/color_tag.h"
#include"rena/renarich.h"

template<class _CharT>
int rena::builtin::nwrprintf( const std::basic_string<_CharT>& __c_s_str , std::basic_ostream<_CharT>& __os , bool __b_style_reset ){
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

    std::size_t lpos = 0;
    if ( __b_style_reset )
    {
        __os << rich_reset;
    }
    while ( rit != rend )
    {
        std::match_results<_string_const_iterator> match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_s_str[bpos-1] != '\\' ) )
        {
            _string tag_str = match[1].str();
            std::basic_stringstream<_CharT> ss( tag_str );
            std::vector<color_code> codes;
            _string this_tag;
            if constexpr ( is_wchar_mode )
            {
                while ( std::getline( ss , this_tag , L',' ) )
                {
                    color_code this_code = parse_color_tag( this_tag );
                    if ( this_code == IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                    codes.push_back( this_code );
                }
            } // wchar
            else
            {
                while ( std::getline( ss , this_tag , ',' ) )
                {
                    color_code this_code = parse_color_tag( this_tag );
                    if ( this_code == IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                    codes.push_back( this_code );
                }
            } // char
            __os << __c_s_str.substr( lpos , bpos - lpos );
            for ( const auto& code : codes )
            {
                if ( code == PopColorTag )
                {
                    __os << rich_pop();
                } // pop tag
                else if ( code == PopAllColorTag )
                {
                    __os << rich_reset;
                } // pop all tag
                else
                {
                    __os << code;
                } // color tag
                // illegal color tag should never approach here
            }
            lpos = epos;
        }
next_iterator:
        ++rit;
    }
    if ( lpos < __c_s_str.size() )
    {
        __os << __c_s_str.substr( lpos );
    } // print remaining chars
    if ( __b_style_reset )
    {
        __os << rich_reset;
    }
    __os << std::flush;
    return 0;
}

template int rena::builtin::nwrprintf<char>( const std::string& , std::ostream& , bool );
template int rena::builtin::nwrprintf<wchar_t>( const std::wstring& , std::wostream& , bool );
