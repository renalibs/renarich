#include"rena/renarichxx.h"

#include<cstdarg>
#include<iostream>
#include<string>

#include"builtin/nwrprintf.h"

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
    return builtin::nwrprintf( fullstr , std::cout );;
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
    return builtin::nwrprintf( fullwstr , std::wcout );
}
