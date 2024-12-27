#ifndef __RENALIBS_RENARICH_BUILTIN_TERMINAL_HELPER_H__
#define __RENALIBS_RENARICH_BUILTIN_TERMINAL_HELPER_H__

#ifdef _WIN32
#include<windows.h>
#else // _WIN32
#include<sys/ioctl.h>
#include<unistd.h>
#endif // _WIN32

#define DEFAULT_TERMINAL_SIZE_WIDTH  80
#define DEFAULT_TERMINAL_SIZE_HEIGHT 25

namespace rena::builtin {

    typedef struct coord {
        int _i_x;
        int _i_y;
    } coord;

    coord get_terminal_size();

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_TERMINAL_HELPER_H__
