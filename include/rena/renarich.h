#ifndef __RENALIBS_RENARICH_H__
#define __RENALIBS_RENARICH_H__

#ifndef _WIN32
#define RENARICH_USE_ANSI
#endif // _WIN32

#include<memory>
#include<ostream>
#include<stack>
#ifndef RENARICH_USE_ANSI
#include<windows.h>
#endif // RENARICH_USE_ANSI

#define RENARICH_DECLARE_STATIC_CLASS( class )  \
    class() = delete;                           \
    class( const class& ) = delete;             \
    class( class&& ) = delete;                  \
    class& operator=( const class& ) = delete;  \
    class& operator=( class&& ) = delete;       \
    ~class() = delete

namespace rena {

    typedef struct color_code {
        unsigned char _u8i_ansi;
        unsigned char _u8i_win32;
        unsigned char _u8i_type;
        const char* _s_name;
        std::string to_string() const {
            return std::string( this -> _s_name );
        }
    } color_code;
    inline bool operator==( const color_code& __c__lhs , const color_code& __c__rhs ){
        return ( ( __c__lhs._u8i_ansi == __c__rhs._u8i_ansi ) && ( __c__lhs._u8i_win32 == __c__rhs._u8i_win32 ) && ( __c__lhs._u8i_type == __c__rhs._u8i_type ) );
    }
    inline bool operator!=( const color_code& __c__lhs , const color_code& __c__rhs ){
        return ( ( __c__lhs._u8i_ansi != __c__rhs._u8i_ansi ) || ( __c__lhs._u8i_win32 != __c__rhs._u8i_win32 ) || ( __c__lhs._u8i_type != __c__rhs._u8i_type ) );
    }

    namespace builtin {

        constexpr unsigned char ColorCodeTypeForegroundColor = 0;
        constexpr unsigned char ColorCodeTypeBackgroundColor = 1;
        constexpr unsigned char ColorCodeTypeStyle = 2;

#ifndef RENARICH_USE_ANSI

        class win32_cs_helper {

            public:
                RENARICH_DECLARE_STATIC_CLASS( win32_cs_helper );

                static void initialize(){
                    _w_hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
                    CONSOLE_SCREEN_BUFFER_INFO csbufinfo;
                    GetConsoleScreenBufferInfo( _w_hstdout , &csbufinfo );
                    _w_ocattr = csbufinfo.wAttributes;
                    _w_fgcattr = _w_ocattr & 0x0F;
                    _w_bgcattr = ( _w_ocattr >> 4 ) & 0x0F;
                    _b_started = true;
                    return;
                }

                static void set_color( WORD _w_fgc , WORD _w_bgc ){
                    if ( !_b_started )
                    {
                        initialize();
                    }

                    if ( _w_fgc != KeepColor )
                    {
                        _w_fgcattr = _w_fgc;
                    }
                    if ( _w_bgc != KeepColor )
                    {
                        _w_bgcattr = _w_bgc;
                    }
                    SetConsoleTextAttribute( _w_hstdout , _w_fgcattr | _w_bgcattr );
                    return;
                }

                static void reset_color(){
                    if ( !_b_started )
                    {
                        initialize();
                    }

                    _w_fgcattr = _w_ocattr & 0x0F;
                    _w_bgcattr = ( _w_ocattr >> 4 ) & 0x0F;
                    SetConsoleTextAttribute( _w_hstdout , _w_ocattr );
                    return;
                }

                static void clear_line(){
                    if ( !_b_started )
                    {
                        initialize();
                    }

                    CONSOLE_SCREEN_BUFFER_INFO csbufinfo;
                    GetConsoleScreenBufferInfo( _w_hstdout , &csbufinfo );
                    COORD cp = { 0 , csbufinfo.dwCursorPosition.Y };
                    SetConsoleCursorPosition( _w_hstdout , cp );
                    DWORD cw;
                    FillConsoleOutputCharacter( _w_hstdout , ' ' , csbufinfo.dwSize.X , cp , &cw );
                    SetConsoleCursorPosition( _w_hstdout , cp );
                    return;
                }

                static constexpr WORD KeepColor = 0xffff;

            private:
                static inline bool _b_started = false;
                static inline HANDLE _w_hstdout; // stdout handle
                static inline WORD _w_ocattr; // original color attribute
                static inline WORD _w_fgcattr; // foreground color attribute
                static inline WORD _w_bgcattr; // background color attribute

        }; // win32_cs_helper: win32 console screen helperd

#endif // RENARICH_USE_ANSI

        class ccstack {

            public:
                ccstack(){}
                ~ccstack(){}

                inline void push( const color_code& __c_cc_code ){
                    if ( this -> _b_enable )
                    {
                        this -> _scc_cs.push( __c_cc_code );
                    }
                    return;
                }

                inline void pop(){
                    if ( this -> _b_enable )
                    {
                        this -> _scc_cs.pop();
                    }
                    return;
                }

                void clear(){
                    if ( this -> _b_enable )
                    {
                        while ( !( this -> _scc_cs.empty() ) )
                        {
                            this -> _scc_cs.pop();
                        }   
                    }
                    return;
                }

                inline bool enable() const noexcept {
                    return this -> _b_enable;
                }

                inline void enable( bool __b_enable ){
                    this -> _b_enable = __b_enable;
                    return;
                }

                inline std::stack<color_code> copy() const {
                    return _scc_cs;
                }

                static inline std::shared_ptr<ccstack> global(){
                    if ( !_p_ccs_gstack )
                    {
                        _p_ccs_gstack = std::make_shared<ccstack>();
                    }
                    return _p_ccs_gstack;
                }

            private:
                std::stack<color_code> _scc_cs; // code stack
                bool _b_enable = true;

                static inline std::shared_ptr<ccstack> _p_ccs_gstack = nullptr; // global color code stack

        }; // class ccstack

    } // namespace builtin

    class fcolor {

        public:
            RENARICH_DECLARE_STATIC_CLASS( fcolor );

            static constexpr color_code BLACK = { 30 , 0x0000 , builtin::ColorCodeTypeForegroundColor , "black" };
            static constexpr color_code RED = { 31 , 0x0004 , builtin::ColorCodeTypeForegroundColor , "red" };
            static constexpr color_code GREEN = { 32 , 0x0002 , builtin::ColorCodeTypeForegroundColor , "green" };
            static constexpr color_code YELLOW = { 33 , 0x0006 , builtin::ColorCodeTypeForegroundColor , "yellow" };
            static constexpr color_code BLUE = { 34 , 0x0001 , builtin::ColorCodeTypeForegroundColor , "blue" };
            static constexpr color_code MAGENTA = { 35 , 0x0005 , builtin::ColorCodeTypeForegroundColor , "magenta" };
            static constexpr color_code CYAN = { 36 , 0x0003 , builtin::ColorCodeTypeForegroundColor , "cyan" };
            static constexpr color_code WHITE = { 37 , 0x0007 , builtin::ColorCodeTypeForegroundColor , "white" };
            static constexpr color_code GRAY = { 90 , 0x0008 , builtin::ColorCodeTypeForegroundColor , "gray" };
            static constexpr color_code BRIGHTRED = { 91 , 0x000C , builtin::ColorCodeTypeForegroundColor , "bright red" };
            static constexpr color_code BRIGHTGREEN = { 92 , 0x000A , builtin::ColorCodeTypeForegroundColor , "bright green" };
            static constexpr color_code BRIGHTYELLOW = { 93 , 0x000E , builtin::ColorCodeTypeForegroundColor , "bright yellow" };
            static constexpr color_code BRIGHTBLUE = { 94 , 0x0009 , builtin::ColorCodeTypeForegroundColor , "bright blue" };
            static constexpr color_code BRIGHTMAGENTA = { 95 , 0x000D , builtin::ColorCodeTypeForegroundColor , "bright magenta" };
            static constexpr color_code BRIGHTCYAN = { 96 , 0x000B , builtin::ColorCodeTypeForegroundColor , "bright cyan" };
            static constexpr color_code BRIGHTWHITE = { 97 , 0x000F , builtin::ColorCodeTypeForegroundColor , "bright white" };

    }; // class fcolor

    class bcolor {

        public:
            RENARICH_DECLARE_STATIC_CLASS( bcolor );

            static constexpr color_code BLACK = { 40 , 0x0000 , builtin::ColorCodeTypeBackgroundColor , "black" };
            static constexpr color_code RED = { 41 , 0x0040 , builtin::ColorCodeTypeBackgroundColor , "red" };
            static constexpr color_code GREEN = { 42 , 0x0020 , builtin::ColorCodeTypeBackgroundColor , "green" };
            static constexpr color_code YELLOW = { 43 , 0x0060 , builtin::ColorCodeTypeBackgroundColor , "yellow" };
            static constexpr color_code BLUE = { 44 , 0x0010 , builtin::ColorCodeTypeBackgroundColor , "blue" };
            static constexpr color_code MAGENTA = { 45 , 0x0050 , builtin::ColorCodeTypeBackgroundColor , "magenta" };
            static constexpr color_code CYAN = { 46 , 0x0030 , builtin::ColorCodeTypeBackgroundColor , "cyan" };
            static constexpr color_code WHITE = { 47 , 0x0070 , builtin::ColorCodeTypeBackgroundColor , "white" };
            static constexpr color_code GRAY = { 100 , 0x0080 , builtin::ColorCodeTypeBackgroundColor , "gray" };
            static constexpr color_code BRIGHTRED = { 101 , 0x00C0 , builtin::ColorCodeTypeBackgroundColor , "bright red" };
            static constexpr color_code BRIGHTGREEN = { 102 , 0x00A0 , builtin::ColorCodeTypeBackgroundColor , "bright green" };
            static constexpr color_code BRIGHTYELLOW = { 103 , 0x00E0 , builtin::ColorCodeTypeBackgroundColor , "bright yellow" };
            static constexpr color_code BRIGHTBLUE = { 104 , 0x0090 , builtin::ColorCodeTypeBackgroundColor , "bright blue" };
            static constexpr color_code BRIGHTMAGENTA = { 105 , 0x00D0 , builtin::ColorCodeTypeBackgroundColor , "bright magenta" };
            static constexpr color_code BRIGHTCYAN = { 106 , 0x00B0 , builtin::ColorCodeTypeBackgroundColor , "bright cyan" };
            static constexpr color_code BRIGHTWHITE = { 107 , 0x00F0 , builtin::ColorCodeTypeBackgroundColor , "bright white" };

    }; // class bcolor

#ifdef RENARICH_USE_ANSI

    class fstyle {

        public:
            RENARICH_DECLARE_STATIC_CLASS( fstyle );

            static constexpr color_code BOLD = { 1 , 0x00FF , builtin::ColorCodeTypeStyle , "bold" };
            static constexpr color_code DIM = { 2 , 0x00FF , builtin::ColorCodeTypeStyle , "dim" };
            static constexpr color_code ITALIC = { 3 , 0x00FF , builtin::ColorCodeTypeStyle , "italic" };
            static constexpr color_code UNDERLINE = { 4 , 0x00FF , builtin::ColorCodeTypeStyle , "underline" };
            static constexpr color_code OVERLINE = { 53 , 0x00FF , builtin::ColorCodeTypeStyle , "overline" };
            static constexpr color_code STRIKE = { 9 , 0x00FF , builtin::ColorCodeTypeStyle , "strike" };
            static constexpr color_code REVERSE = { 7 , 0x00FF , builtin::ColorCodeTypeStyle , "reverse" };

    }; // class fstyle

#endif // RENARICH_USE_ANSI

    template<class _Elem , class _Traits>
    std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const color_code& __c_cc_code ){
#ifdef RENARICH_USE_ANSI
        __os << "\033[" << static_cast<int>( __c_cc_code._u8i_ansi ) << "m";
#else // RENARICH_USE_ANSI
        switch ( __c_cc_code._u8i_type ) {
            case builtin::ColorCodeTypeForegroundColor: builtin::win32_cs_helper::set_color( __c_cc_code._u8i_win32 , builtin::win32_cs_helper::KeepColor ); break;
            case builtin::ColorCodeTypeBackgroundColor: builtin::win32_cs_helper::set_color( builtin::win32_cs_helper::KeepColor , __c_cc_code._u8i_win32 ); break;
            default: break;
        }
#endif // RENARICH_USE_ANSI
        builtin::ccstack::global() -> push( __c_cc_code );
        return __os;
    }

    typedef struct _s_rich_pop {
        unsigned int _ui_num;
    } _s_rich_pop;
    
    inline _s_rich_pop rich_pop( unsigned int __ui_num = 1 ){
        return { __ui_num };
    }

    template<class _Elem , class _Traits>
    std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , _s_rich_pop __elem ){
#ifdef RENARICH_USE_ANSI
        __os << "\033[0m" << std::flush;
#else // RENARICH_USE_ANSI
        builtin::win32_cs_helper::reset_color();
#endif // RENARICH_USE_ANSI
        for ( unsigned int i = 0 ; i < __elem._ui_num ; i++ )
        {
            builtin::ccstack::global() -> pop();
        }
        auto code_stack = builtin::ccstack::global() -> copy();
        builtin::ccstack::global() -> enable( false );
        // disable global ccstack before reverting older color codes
        // otherwise older color codes will be pushed into stack again
        while ( !code_stack.empty() )
        {
            __os << code_stack.top();
            code_stack.pop();
        }
        builtin::ccstack::global() -> enable( true );
        return __os;
    }

    template<class _Elem , class _Traits>
    std::basic_ostream<_Elem,_Traits>& rich_reset( std::basic_ostream<_Elem,_Traits>& __os ){
#ifdef RENARICH_USE_ANSI
        __os << "\033[0m" << std::flush;
#else // RENARICH_USE_ANSI
        builtin::win32_cs_helper::reset_color();
#endif // RENARICH_USE_ANSI
        builtin::ccstack::global() -> clear();
        return __os;
    }

    template<class _Elem , class _Traits>
    std::basic_ostream<_Elem,_Traits>& clear_line( std::basic_ostream<_Elem,_Traits>& __os ){
#ifdef RENARICH_USE_ANSI
        __os << "\033[2K\r" << std::flush;
#else // RENARICH_USE_ANSI
        builtin::win32_cs_helper::clear_line();
#endif // RENARICH_USE_ANSI
        return __os;
    }

} // namespace rena

#endif // __RENALIBS_RENARICH_H__
