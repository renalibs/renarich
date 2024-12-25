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
