#ifndef __RENALIBS_RENARICH_BUILTIN_TOKENIZE_H__
#define __RENALIBS_RENARICH_BUILTIN_TOKENIZE_H__

#include<string>
#include<vector>

#ifdef RENARICH_USE_ICU
#include"unicode/unistr.h"
#endif // RENARICH_USE_ICU

namespace rena::builtin {

    template<class _CharT>
    std::basic_string<_CharT> nwstr_erase_ct( const std::basic_string<_CharT>& __c_s_str );

#ifdef RENARICH_USE_ICU
    icu::UnicodeString ustr_erase_ct( const icu::UnicodeString& __c_us_str );

    typedef struct token {
        icu::UnicodeString _us_str;
        int _i_width;
        typedef struct _cc_pos {
            int _i_pos;
            icu::UnicodeString _us_ctstr;
        } _ct_pos;
        std::vector<_ct_pos> _v_cts;

        icu::UnicodeString to_ct_string( int __i_pos = 0 ) const;
    } token;
    std::vector<token> tokenize( const icu::UnicodeString& __c_us_str );
#endif // RENARICH_USE_ICU

// *****************************
// TODO: tokenize no icu version
// *****************************

} // namespace rena::builtin

#endif // __RENALIBS_RENARICH_BUILTIN_TOKENIZE_H__
