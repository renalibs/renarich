#include"rena/renarichxx.h"

#include<cstdarg>
#include<iostream>
#include<regex>
#include<sstream>
#include<stack>
#include<string>

#include"builtin/color_tag.h"

template<class _CharT>
int _rprintf( const std::basic_string<_CharT>& __c_s_str , std::basic_ostream<_CharT>& __os );

int rena::rprintf( const char* __cp_c_format , ... ){
    va_list args;
    va_start( args , __cp_c_format );

    va_list args_copy;
    va_copy( args_copy , args );
    int len = vsnprintf( nullptr , 0 , __cp_c_format , args_copy );
    va_end( args_copy );

    char* buf = new char[len];
    vsnprintf( buf , len , __cp_c_format , args );
    std::string fullstr( buf );
    delete[] buf;
    va_end( args );
    return _rprintf( fullstr , std::cout );;
}

int rena::wrprintf( const wchar_t* __cp_wc_format , ... ){
    va_list args;
    va_start( args , __cp_wc_format );

    va_list args_copy;
    va_copy( args_copy , args );
    int len = vswprintf( nullptr , 0 , __cp_wc_format , args_copy );
    va_end( args_copy );

    wchar_t* buf = new wchar_t[len];
    vswprintf( buf , len , __cp_wc_format , args );
    std::wstring fullwstr( buf );
    delete[] buf;
    va_end( args );
    return _rprintf( fullwstr , std::wcout );
}

template<class _CharT>
int _rprintf( const std::basic_string<_CharT>& __c_s_str , std::basic_ostream<_CharT>& __os ){
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
    std::stack<rena::color_code> code_stack;
    while ( rit != rend )
    {
        std::match_results<_string_const_iterator> match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_s_str[bpos-1] != '\\' ) )
        {
            _string tag_str = match[1].str();
            std::basic_stringstream<_CharT> ss( tag_str );
            std::vector<rena::color_code> codes;
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
                    codes.push_back( this_code );
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
                    codes.push_back( this_code );
                }
            } // char
            __os << __c_s_str.substr( lpos , bpos - lpos );
            for ( const auto& code : codes )
            {
                if ( code == rena::builtin::PopColorTag )
                {
                    __os << rena::rich_reset;
                    if ( !code_stack.empty() )
                    {
                        code_stack.pop();
                        std::stack<rena::color_code> temp_stack( code_stack );
                        while ( !code_stack.empty() )
                        {
                            __os << code_stack.top();
                            code_stack.pop();
                        }
                        code_stack = temp_stack;
                    } // code stack not empty, revert remaining color codes
                } // pop tag
                else if ( code == rena::builtin::PopAllColorTag )
                {
                    __os << rena::rich_reset;
                    while ( !code_stack.empty() )
                    {
                        code_stack.pop();
                    } // pop all codes
                } // pop all tag
                else
                {
                    __os << code;
                    code_stack.push( code );
                } // color tag
                // illegal color tag should never approach here
                lpos = epos;
            }
        }
next_iterator:
        ++rit;
    }
    if ( lpos < __c_s_str.size() )
    {
        __os << __c_s_str.substr( lpos );
    } // print remaining chars
    __os << rena::rich_reset << std::flush;
    return 0;
}

template int _rprintf<char>( const std::string& __c_s_str , std::ostream& __os );
template int _rprintf<wchar_t>( const std::wstring& __c_s_str , std::wostream& __os );
