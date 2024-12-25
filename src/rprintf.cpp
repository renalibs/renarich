#include"rena/renarichxx.h"
#include"rena/renarich.h"

#include<codecvt>
#include<cstdarg>
#include<iostream>
#include<regex>
#include<stack>
#include<string>

#include"builtin/color_tag.h"

int _rprintf( const std::string& __c_s_str , std::ostream& __os );
int _wrprintf( const std::wstring& __c_ws_str , std::wostream & __wos );

int rena::rprintf( const char* __cp_c_format , ... ){
    va_list args;
    va_start( args , __cp_c_format );
    char* buf = new char[65536];
    vsnprintf( buf , 65536 , __cp_c_format , args );
    std::string fullstr( buf );
    delete[] buf;
    va_end( args );
    return _rprintf( fullstr , std::cout );;
}

int rena::wrprintf( const wchar_t* __cp_wc_format , ... ){
    va_list args;
    va_start( args , __cp_wc_format );
    wchar_t* buf = new wchar_t[65536];
    vswprintf( buf , 65536 , __cp_wc_format , args );
    std::wstring fullwstr( buf );
    delete[] buf;
    va_end( args );
    return _wrprintf( fullwstr , std::wcout );
}

int _rprintf( const std::string& __c_s_str , std::ostream& __os ){
    std::regex rbranket( R"(\[(.*?)\])" );
    std::sregex_iterator rit( __c_s_str.begin() , __c_s_str.end() , rbranket );
    std::sregex_iterator rend;

    std::size_t lpos = 0;
    std::stack<rena::_color_code> code_stack;
    while ( rit != rend )
    {
        std::smatch match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_s_str[bpos-1] != '\\' ) )
        {
            std::string tag_str = match[1].str();
            std::stringstream ss( tag_str );
            std::vector<std::string> tags;
            std::string this_tag;
            while ( std::getline( ss , this_tag , ',' ) )
            {
                if ( !rena::builtin::is_legal_color_tag( this_tag ) )
                {
                    goto next_iterator;
                } // illegal color tag, break
                tags.push_back( this_tag );
            }
            __os << __c_s_str.substr( lpos , bpos - lpos );
            for ( const auto& tag : tags )
            {
                rena::_color_code code = rena::builtin::parse_color_tag( tag );
                if ( code == rena::builtin::PopColorTag )
                {
                    __os << rena::rich_reset;
                    code_stack.pop();
                    if ( !code_stack.empty() )
                    {
                        std::stack<rena::_color_code> temp_stack( code_stack );
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
                else if ( code != rena::builtin::IllegalColorTag )
                {
                    __os << code;
                    code_stack.push( code );
                } // color tag
                else
                {
                    goto next_iterator;
                } // illegal tag, should never approach here
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

int _wrprintf( const std::wstring& __c_ws_str , std::wostream& __wos ){
    std::wregex rbranket( LR"(\[(.*?)\])" );
    std::wsregex_iterator rit( __c_ws_str.begin() , __c_ws_str.end() , rbranket );
    std::wsregex_iterator rend;

    std::size_t lpos = 0;
    std::stack<rena::_color_code> code_stack;
    while ( rit != rend )
    {
        std::wsmatch match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_ws_str[bpos-1] != '\\' ) )
        {
            std::wstring tag_str = match[1].str();
            std::wstring wtempstr;
            std::wstringstream ss( tag_str );
            std::vector<std::string> tags;
            while ( std::getline( ss , wtempstr , L',' ) )
            {
                std::string this_tag = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes( wtempstr );
                if ( !rena::builtin::is_legal_color_tag( this_tag ) )
                {
                    goto next_iterator;
                } // illegal color tag, break
                tags.push_back( this_tag );
            }
            __wos << __c_ws_str.substr( lpos , bpos - lpos );
            for ( const auto& tag : tags )
            {
                rena::_color_code code = rena::builtin::parse_color_tag( tag );
                if ( code == rena::builtin::PopColorTag )
                {
                    __wos << rena::rich_reset;
                    code_stack.pop();
                    if ( !code_stack.empty() )
                    {
                        std::stack<rena::_color_code> temp_stack( code_stack );
                        while ( !code_stack.empty() )
                        {
                            __wos << code_stack.top();
                            code_stack.pop();
                        }
                        code_stack = temp_stack;
                    } // code stack not empty, revert remaining color codes
                } // pop tag
                else if ( code == rena::builtin::PopAllColorTag )
                {
                    __wos << rena::rich_reset;
                    while ( !code_stack.empty() )
                    {
                        code_stack.pop();
                    } // pop all codes
                } // pop all tag
                else if ( code != rena::builtin::IllegalColorTag )
                {
                    __wos << code;
                    code_stack.push( code );
                } // color tag
                else
                {
                    goto next_iterator;
                } // illegal tag, should never approach here
                lpos = epos;
            }
        }
next_iterator:
        ++rit;
    }
    if ( lpos < __c_ws_str.size() )
    {
        __wos << __c_ws_str.substr( lpos );
    } // print remaining chars
    __wos << rena::rich_reset << std::flush;
    return 0;
}
