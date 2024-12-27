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

#include"rena/renarich.h"

namespace rena {

    class renarichxx_cfg {

        public:
            RENARICH_DECLARE_STATIC_CLASS( renarichxx_cfg );

            __RENALIBS_API__ static bool use_cjk_char_spacing();
            __RENALIBS_API__ static void use_cjk_char_spacing( bool __b_enable );

        private:
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
            basic_panel( const std::basic_string<_CharT>& __c_s_content )
                : basic_rcc<_CharT>() , _s_content( __c_s_content ) {}

            static constexpr int s_title = 0x0001;
            static constexpr int s_no_title = 0x0002;
            static constexpr int s_subtitle = 0x0010;
            static constexpr int s_no_subtitle = 0x0020;
            static constexpr int s_frame_single_line = 0x0100;
            static constexpr int s_frame_double_line = 0x0200;
            static constexpr int s_frame_rounded = 0x0400;
            static constexpr int s_frame_heavy_single_line = 0x0800;
            static constexpr int s_default = s_title | s_subtitle | s_frame_single_line;

            std::basic_string<_CharT> content() const noexcept;
            void content( const std::basic_string<_CharT>& __c_s_content );
            color_code frame_color() const noexcept;
            void frame_color( const color_code& __c_cc_code );
            int style() const noexcept;
            void style( int __i_style );

        protected:
            virtual void _render( std::basic_ostream<_CharT>& __os ) const override;
            virtual int _get_content_width() const = 0;
            virtual int _get_content_width( const std::basic_string<_CharT>& __c_s_content ) const = 0;

            virtual _CharT _get_space_char() const noexcept = 0;
            virtual const std::basic_string<_CharT>& _get_frame_char( int __i_c ) const = 0;

            std::basic_string<_CharT> _s_content;
            color_code _cc_frame_color = fcolor::WHITE;
            int _i_style = s_default;

    }; // class basic_panel

    class panel final : public basic_panel<char> {

        public:
            panel() : basic_panel<char>() {}
            panel( const std::string& __c_s_content )
                : basic_panel<char>( __c_s_content ) {};

        protected:
            int _get_content_width() const override;
            int _get_content_width( const std::string& __c_s_content ) const override;

            char _get_space_char() const noexcept override;
            const std::string& _get_frame_char( int __i_c ) const override;

    }; // class panel

} // namespace rena

#endif // __RENALIBS_RENARICHXX_H__
