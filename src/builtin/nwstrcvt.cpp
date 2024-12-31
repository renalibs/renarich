#include"nwstrcvt.h"

#ifdef _WIN32
#include<windows.h>
#else // _WIN32
#include<codecvt>
#include<locale>
#endif // _WIN32

std::wstring rena::builtin::nwstrcvt_to_wstr( const std::string& __c_s_str , bool __b_force_utf8 ){
#ifdef _WIN32
    int cp = __b_force_utf8 ? CP_UTF8 : CP_ACP;
    int bufsize = MultiByteToWideChar( cp , 0 , __c_s_str.c_str() , -1 , NULL , 0 );
    wchar_t* wcstr = new wchar_t[bufsize];
    MultiByteToWideChar( cp , 0 , __c_s_str.c_str() , -1 , wcstr , bufsize );
    std::wstring wstr( wcstr );
    delete[] wcstr;
    return wstr;
#else // _WIN32
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes( __c_s_str );
#endif // _WIN32
}

std::string rena::builtin::nwstrcvt_to_nstr( const std::wstring& __c_ws_str , bool __b_force_utf8 ){
#ifdef _WIN32
    int cp = __b_force_utf8 ? CP_UTF8 : CP_ACP;
    int bufsize = WideCharToMultiByte( cp , 0 , __c_ws_str.c_str() , -1 , NULL , 0 , NULL , FALSE );
    char* cstr = new char[bufsize];
    WideCharToMultiByte( cp , 0 , __c_ws_str.c_str() , -1 , cstr , bufsize , NULL , FALSE );
    std::string str( cstr );
    delete[] cstr;
    return str;
#else // _WIN32
    return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes( __c_ws_str );
#endif // _WIN32
}
