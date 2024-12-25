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

    rena::wrprintf( LR"(你好！我启用了%ls下的宽字符输出扩展，[red]你应该能够正确看到这段文字！[/]
[byellow]如果你看到了一堆乱码的话，也许你应该检查一下编译选项哪里出了问题。[/])" , L"Windows系统" );

    return 0;
}
