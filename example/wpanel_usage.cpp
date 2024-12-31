#include<fcntl.h>
#include<io.h>
#include<iostream>

#include"rena/renarichxx.h"

#ifdef _MSC_VER
int wmain(){
#else // _MSC_VER
int main(){
#endif // _MSC_VER
    _setmode( _fileno( stdout ) , _O_WTEXT );
    _setmode( _fileno( stderr ) , _O_WTEXT );

    rena::wpanel wp;
    wp.title( L"标题" );
    wp.subtitle( L"副标题" );
    wp.push_line( L"第一行" );
    wp.push_line( L"[cyan]第二行" );
    wp.push_line( L"[italic,underline,overline,magenta]第三行：相对复杂的测试" );
    std::wcout << wp << std::endl;

    return 0;
}
