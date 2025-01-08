#include"rena/renarichxx.h"
#include"rena/renarich_errcodes.h"
#include"rena/renarich_exceptions.h"

#include<memory>
#include<string>

#include"builtin/console_helper.h"
#include"builtin/tokenize.h"
#ifdef RENARICH_USE_ICU
#include"builtin/ucwidth.h"
#include"unicode/regex.h"
#include"unicode/ustring.h"
#include"unicode/utypes.h"
#include"unicode/unistr.h"
#endif // RENARICH_USE_ICU

#ifdef RENARICH_USE_ICU

void _ustr_trim_back( icu::UnicodeString& __us_str ){
    UErrorCode status = U_ZERO_ERROR;
    std::unique_ptr<icu::RegexPattern> rbackws( icu::RegexPattern::compile( UNICODE_STRING_SIMPLE( R"(\s+$)" ) , 0 , status ) );
    if ( U_FAILURE( status ) )
    {
        throw rena::exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_COMPILE_FAILED , "rbackws compile failed" );
    }
    std::unique_ptr<icu::RegexMatcher> rmatcher( rbackws -> matcher( __us_str , status ) );
    if ( U_FAILURE( status ) )
    {
        throw rena::exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_MATCH_FAILED , "rbackws match failed" );
    }
    icu::UnicodeString ustr = rmatcher -> replaceAll( UNICODE_STRING_SIMPLE( "" ) , status );
    if ( U_FAILURE( status ) )
    {
        throw rena::exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_MATCH_REPLACE_FAILED , "rbackws replaceall failed" );
    }
    __us_str = ustr;
    return;
}

#endif // RENARICH_USE_ICU

template<class _CharT>
std::basic_string<_CharT> rena::basic_rcc<_CharT>::_get_content_without_color_tag( const std::basic_string<_CharT>& __c_s_str ){
    return builtin::nwstr_erase_ct( __c_s_str );
}

template<class _CharT>
std::vector<std::basic_string<_CharT>> rena::basic_rcc<_CharT>::_spilt_line_to_lines( const std::basic_string<_CharT>& __c_s_str , int __i_diff ){
    using _string = std::basic_string<_CharT>;

    constexpr bool is_wchar_mode = ( std::is_same_v<_CharT,wchar_t> );
    const int max_width = builtin::get_console_size()._i_x + __i_diff;

#ifdef RENARICH_USE_ICU
    icu::UnicodeString ustr;
    if constexpr ( is_wchar_mode )
    {
#ifdef _WIN32
        ustr = __c_s_str;
#else // _WIN32
        ustr = icu::UnicodeString::fromUTF32( reinterpret_cast<const UChar32*>( __c_s_str.c_str() )  , __c_s_str.size() );
#endif // _WIN32
    }
    else
    {
        ustr = icu::UnicodeString::fromUTF8( __c_s_str );
    }

    UErrorCode status = U_ZERO_ERROR;
    std::vector<builtin::token> tokens = builtin::tokenize( ustr );

    std::vector<icu::UnicodeString> lines;
    icu::UnicodeString this_line;
    int this_line_width = 0;
    for ( const auto& it : tokens )
    {
        if ( this_line_width + it._i_width <= max_width )
        {
            this_line += it.to_ct_string();
            this_line_width += it._i_width;
        } // append word to line
        else
        {
            _ustr_trim_back( this_line );
            lines.push_back( this_line );
            this_line.remove();
            this_line_width = 0;
            // push line
            if ( it._i_width > max_width )
            {
                icu::UnicodeString this_word = it._us_str;
                int this_word_width = it._i_width;
                auto it_this_word_vct = it._v_cts.begin();
                int i = 0;
                while ( this_word_width > max_width )
                {
                    for ( ; i < this_word.length() ; i++ )
                    {
                        UChar32 this_uc32 = this_word.char32At( i );
                        int this_uc32_width = builtin::ucwidth( this_uc32 );
                        if ( this_line_width + this_uc32_width > max_width )
                        {
                            break;
                        }
                        this_line += this_uc32;
                        this_line_width += this_uc32_width;
                        if ( ( it_this_word_vct != it._v_cts.end() ) && ( i == it_this_word_vct -> _i_pos ) )
                        {
                            this_line += it_this_word_vct -> _us_ctstr;
                            ++it_this_word_vct;
                        }
                    }
                    _ustr_trim_back( this_line );
                    lines.push_back( this_line );
                    this_word_width -= this_line_width;
                    this_line.remove();
                    this_line_width = 0;
                } // create & push lines from this word
                this_line = it.to_ct_string( i );
                this_line_width = this_word_width;
            } // word wider than max_width
            else
            {
                this_line = it.to_ct_string();
                this_line_width = it._i_width;
            }
        } // line full
    }
    _ustr_trim_back( this_line );
    if ( !this_line.isEmpty() && !icu::UnicodeString( this_line ).trim().isEmpty() )
    {
        lines.push_back( this_line );
    } // last line contains non-whitespace chars

    std::vector<_string> lines_out;
    for ( const auto& it : lines )
    {
        _string this_line;
        if constexpr ( is_wchar_mode )
        {
            int size = 0;
            u_strToWCS( nullptr , 0 , &size , it.getBuffer() , it.length() , &status );
            this_line.resize( size );
            u_strToWCS( this_line.data() , this_line.size() , nullptr , it.getBuffer() , it.length() , &status );
        }
        else
        {
            it.toUTF8String( this_line );
            // std::cout << this_line << std::endl;
        }
        lines_out.push_back( this_line );
    }

    return lines_out;    

#else // RENARICH_USE_ICU

    return { __c_s_str };

    // *****************************************
    // TODO: _spilt_line_to_lines no icu version
    // *****************************************

#endif // RENARICH_USE_ICU
}

template class rena::basic_rcc<char>;
template class rena::basic_rcc<wchar_t>;
