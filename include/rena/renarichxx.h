#ifndef __RENALIBS_RENARICHXX_H__
#define __RENALIBS_RENARICHXX_H__

#ifdef __RENARICH_HEADER_ONLY__
#error "This header cannot be included when `RENARICH_HEADER_ONLY` flag has been set to `ON`"
#endif

#ifdef _MSC_VER
    #ifdef __RENALIBS_EXPORT__
        #define __RENALIBS_API__ __declspec( dllexport )
    #else
        #define __RENALIBS_API__ __declspec( dllimport )
    #endif //__RENALIBS_EXPORT__
#else // _MSC_VER
    #define __RENALIBS_API__
#endif // _MSC_VER

#include<ostream>
#include<string>
#include<vector>

#include"rena/renarich.h"

namespace rena {

    class renarichxx_cfg {

        public:
            RENARICH_DECLARE_STATIC_CLASS( renarichxx_cfg );

            __RENALIBS_API__ static bool force_utf8_codecvt();
            __RENALIBS_API__ static void force_utf8_codecvt( bool __b_enable );
            __RENALIBS_API__ static bool use_cjk_char_spacing();
            __RENALIBS_API__ static void use_cjk_char_spacing( bool __b_enable );

        private:
            static bool _b_force_utf8_codecvt;
            static bool _b_use_cjk_char_spacing;

    }; // class renarichxx_cfg

    __RENALIBS_API__ int rprintf( const char* __cp_c_format , ... );
    __RENALIBS_API__ int wrprintf( const wchar_t* __cp_wc_format , ... );

    template<class _CharT>
    class basic_rcc {

        public:
            basic_rcc(){}
            virtual ~basic_rcc(){}

            template<class _Elem , class _Traits>
            friend std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const basic_rcc<_Elem>& __c__rcc );

        protected:
            virtual void _render( std::basic_ostream<_CharT>& __os ) const = 0;
            static std::basic_string<_CharT> _get_content_without_color_tag( const std::basic_string<_CharT>& __c_s_str );

    }; // class basic_rcc: basic rich CLI control

    template<class _Elem , class _Traits>
    inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const basic_rcc<_Elem>& __c__rcc ){
        __c__rcc._render( __os );
        return __os;
    }

    template<class _CharT>
    class basic_panel : public basic_rcc<_CharT> {

        public:
            basic_panel() : basic_rcc<_CharT>() {}
            basic_panel( const std::basic_string<_CharT>& __c_s_line )
                : basic_rcc<_CharT>() , _vs_content( { __c_s_line } ) {}
            basic_panel( const std::vector<std::basic_string<_CharT>>& __c_vs_content )
                : basic_rcc<_CharT>() , _vs_content( __c_vs_content ) {}

            static constexpr unsigned int s_title = 0x0001;
            static constexpr unsigned int s_no_title = 0x0002;
            static constexpr unsigned int s_subtitle = 0x0010;
            static constexpr unsigned int s_no_subtitle = 0x0020;
            static constexpr unsigned int s_frame_single_line = 0x0100;
            static constexpr unsigned int s_frame_double_line = 0x0200;
            static constexpr unsigned int s_frame_rounded = 0x0400;
            static constexpr unsigned int s_frame_heavy_single_line = 0x0800;
            static constexpr unsigned int s_default = s_title | s_subtitle | s_frame_single_line;

            __RENALIBS_API__ std::vector<std::basic_string<_CharT>> content() const noexcept;
            __RENALIBS_API__ void content( const std::vector<std::basic_string<_CharT>>& __c_vs_content );
            __RENALIBS_API__ void push_line( const std::basic_string<_CharT>& __c_s_line );
            __RENALIBS_API__ void insert_line( const std::basic_string<_CharT>& __c_s_line , std::size_t __ull_pos );
            __RENALIBS_API__ void pop_line();
            __RENALIBS_API__ void erase_line( std::size_t __ull_pos );
            __RENALIBS_API__ std::basic_string<_CharT> title() const noexcept;
            __RENALIBS_API__ void title( const std::basic_string<_CharT>& __c_s_title );
            __RENALIBS_API__ std::basic_string<_CharT> subtitle() const noexcept;
            __RENALIBS_API__ void subtitle( const std::basic_string<_CharT>& __c_s_subtitle );
            __RENALIBS_API__ color_code frame_color() const noexcept;
            __RENALIBS_API__ void frame_color( const color_code& __c_cc_code );
            __RENALIBS_API__ unsigned int style() const noexcept;
            __RENALIBS_API__ void style( unsigned int __ui_style );

        protected:
            virtual void _render( std::basic_ostream<_CharT>& __os ) const override;
            virtual int _get_content_width( const std::basic_string<_CharT>& __c_s_content ) const = 0;

            virtual _CharT _get_space_char() const noexcept = 0;
            virtual const std::basic_string<_CharT>& _get_frame_char( int __i_c ) const = 0;

            std::vector<std::basic_string<_CharT>> _vs_content;
            std::basic_string<_CharT> _s_title;
            std::basic_string<_CharT> _s_subtitle;
            color_code _cc_frame_color = fcolor::WHITE;
            unsigned int _ui_style = s_default;

    }; // class basic_panel

    class panel final : public basic_panel<char> {

        public:
            __RENALIBS_API__ panel() : basic_panel<char>() {}
            __RENALIBS_API__ panel( const std::string& __c_s_line )
                : basic_panel<char>( __c_s_line ) {}
            __RENALIBS_API__ panel( const std::vector<std::string>& __c_vs_content )
                : basic_panel<char>( __c_vs_content ) {}

        protected:
            int _get_content_width( const std::string& __c_s_content ) const override;

            char _get_space_char() const noexcept override;
            const std::string& _get_frame_char( int __i_c ) const override;

    }; // class panel

    class wpanel final : public basic_panel<wchar_t> {

        public:
            __RENALIBS_API__ wpanel() : basic_panel<wchar_t>() {}
            __RENALIBS_API__ wpanel( const std::wstring& __c_ws_line )
                : basic_panel<wchar_t>( __c_ws_line ) {}
            __RENALIBS_API__ wpanel( const std::vector<std::wstring>& __c_vws_content )
                : basic_panel<wchar_t>( __c_vws_content ) {}

        protected:
            int _get_content_width( const std::wstring& __c_s_content ) const override;

            wchar_t _get_space_char() const noexcept override;
            const std::wstring& _get_frame_char( int __i_c ) const override;

    }; // class wpanel

    template<class _CharT>
    class basic_rstring : public std::basic_string<_CharT> , public basic_rcc<_CharT> {

        public:
            using std::basic_string<_CharT>::basic_string;

            template<class _Elem , class _Traits>
            friend std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const basic_rstring<_Elem>& __c__rstr );

        protected:
            __RENALIBS_API__ virtual void _render( std::basic_ostream<_CharT>& __os ) const override;

    }; // class basic_rstring

    template<class _Elem , class _Traits>
    inline std::basic_ostream<_Elem,_Traits>& operator<<( std::basic_ostream<_Elem,_Traits>& __os , const basic_rstring<_Elem>& __c__rstr ){
        return operator<<( __os , static_cast<const basic_rcc<_Elem>&>( __c__rstr ) );
    }

    typedef basic_rstring<char> rstring;
    typedef basic_rstring<wchar_t> wrstring;

} // namespace rena

#endif // __RENALIBS_RENARICHXX_H__
