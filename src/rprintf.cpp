#include"rena/renarichxx.h"

#include<iostream>
#include<regex>
#include<stack>

#include"builtin/color_tag.h"

int _rprintf( const std::string& __c_s_str , std::ostream& __os );

int rena::rprintf( const char* __cp_c_format , ... ){
    va_list args;
    va_start( args , __cp_c_format );
    char* buf = new char[65536];
    vsnprintf( buf , 65536 , __cp_c_format , args );
    std::string fullstr( buf );
    delete[] buf;
    va_end( args );
    int rc = _rprintf( fullstr , std::cout );
    return rc;
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
            std::string tag = match[1].str();
            rena::_color_code code = rena::builtin::parse_color_tag( tag );
            if ( code == rena::builtin::PopColorTag )
            {
                code_stack.pop();
                __os << __c_s_str.substr( lpos , bpos - lpos ) << rena::rich_reset;
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
                lpos = epos;
            } // pop tag
            else if ( code != rena::builtin::IllegalColorTag )
            {
                __os << __c_s_str.substr( lpos , bpos - lpos ) << code;
                code_stack.push( code );
                lpos = epos;
            } // color tag
            else {} // illegal tag
        }
        ++rit;
    }
    if ( lpos < __c_s_str.size() )
    {
        __os << __c_s_str.substr( lpos );
    } // print remaining chars
    __os << rena::rich_reset << std::flush;
    return 0;
}
