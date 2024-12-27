#include"terminal_helper.h"

rena::builtin::coord rena::builtin::get_terminal_size(){
    coord size = {};
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbufinfo;
    if ( GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ) , &csbufinfo ) )
    {
        size._i_x = csbufinfo.srWindow.Right - csbufinfo.srWindow.Left + 1;
        size._i_y = csbufinfo.srWindow.Bottom - csbufinfo.srWindow.Top + 1;
    }
    else
    {
        size._i_x = DEFAULT_TERMINAL_SIZE_WIDTH;
        size._i_y = DEFAULT_TERMINAL_SIZE_HEIGHT;
    }
#else // _WIN32
    struct winsize ws;
    if ( ioctl( STDOUT_FILENO , TIOCGWINSZ , &ws ) == 0 )
    {
        size._i_x = ws.ws_col;
        size._i_y = ws.ws_row;
    }
    else
    {
        size._i_x = DEFAULT_TERMINAL_SIZE_WIDTH;
        size._i_y = DEFAULT_TERMINAL_SIZE_HEIGHT;
    }
#endif // _WIN32
    return size;
}
