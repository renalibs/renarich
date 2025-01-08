#include"tokenize.h"

#include<iostream>
#include<regex>
#include<sstream>

#include"builtin/color_tag.h"
#include"builtin/ucwidth.h"
#include"rena/renarich_errcodes.h"
#include"rena/renarich_exceptions.h"
#include"rena/renarich.h"
#include"unicode/regex.h"

template<class _CharT>
std::basic_string<_CharT> rena::builtin::nwstr_erase_ct( const std::basic_string<_CharT>& __c_s_str ){
    using _string = std::basic_string<_CharT>;
    using _string_const_iterator = typename _string::const_iterator;

    constexpr bool is_wchar_mode = ( std::is_same_v<_CharT,wchar_t> );

    std::basic_regex<_CharT> rbracket;
    if constexpr ( is_wchar_mode )
    {
        rbracket = std::basic_regex<_CharT>( LR"(\[(.*?)\])" );
    }
    else
    {
        rbracket = std::basic_regex<_CharT>( R"(\[(.*?)\])" );
    }

    std::regex_iterator<_string_const_iterator> rit( __c_s_str.begin() , __c_s_str.end() , rbracket );
    std::regex_iterator<_string_const_iterator> rend;
    std::basic_ostringstream<_CharT> oss;

    std::size_t lpos = 0;
    while ( rit != rend )
    {
        std::match_results<_string_const_iterator> match = *rit;
        std::size_t bpos = match.position();
        std::size_t epos = bpos + match.length();
        if ( bpos == 0 || ( bpos > 0 && __c_s_str[bpos-1] != '\\' ) )
        {
            _string tag_str = match[1].str();
            std::basic_stringstream<_CharT> ss( tag_str );
            _string this_tag;
            if constexpr ( is_wchar_mode )
            {
                while ( std::getline( ss , this_tag , L',' ) )
                {
                    rena::color_code this_code = rena::builtin::parse_color_tag( this_tag );
                    if ( this_code == rena::builtin::IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                }
            } // wchar
            else
            {
                while ( std::getline( ss , this_tag , ',' ) )
                {
                    rena::color_code this_code = rena::builtin::parse_color_tag( this_tag );
                    if ( this_code == rena::builtin::IllegalColorTag )
                    {
                        goto next_iterator;
                    }
                }
            } // char
            oss << __c_s_str.substr( lpos , bpos - lpos );
            lpos = epos;
        }
next_iterator:
        ++rit;
    }
    if ( lpos < __c_s_str.size() )
    {
        oss << __c_s_str.substr( lpos );
    }
    
    return oss.str();
}

template std::string rena::builtin::nwstr_erase_ct<char>( const std::string& );
template std::wstring rena::builtin::nwstr_erase_ct<wchar_t>( const std::wstring& );

#ifdef RENARICH_USE_ICU

icu::UnicodeString rena::builtin::ustr_erase_ct( const icu::UnicodeString& __c_us_str ){
    std::string str;
    __c_us_str.toUTF8String( str );
    return icu::UnicodeString::fromUTF8( nwstr_erase_ct( str ) );
}

icu::UnicodeString rena::builtin::token::to_ct_string( int __i_pos ) const {
    if ( this -> _v_cts.empty() )
    {
        return this -> _us_str.tempSubString( __i_pos );
    } // no color tags

    icu::UnicodeString uctstr;
    auto it_vct = this -> _v_cts.begin();
    while ( it_vct -> _i_pos < __i_pos )
    {
        ++it_vct;
    }
    for ( int i = __i_pos ; i < this -> _us_str.length() ; i++ )
    {
        if ( ( it_vct != this -> _v_cts.end() ) && ( i == it_vct -> _i_pos ) )
        {
            std::string str;
            it_vct -> _us_ctstr.toUTF8String( str );
            uctstr += it_vct -> _us_ctstr;
            ++it_vct;
        }
        uctstr += this -> _us_str[i];
    }
    while ( it_vct != this -> _v_cts.end() )
    {
        uctstr += it_vct -> _us_ctstr;
        ++it_vct;
    }
    return uctstr;
}

std::vector<rena::builtin::token> rena::builtin::tokenize( const icu::UnicodeString& __c_us_str ){
    UErrorCode status = U_ZERO_ERROR;
    std::unique_ptr<icu::RegexPattern> rseparator(
        icu::RegexPattern::compile( UNICODE_STRING_SIMPLE( R"([\s\!\,\.\:\;\?\~！，。：；？]+)" ) , 0 , status )
    );
    if ( U_FAILURE( status ) )
    {
        throw exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_COMPILE_FAILED , "rseparator compile failed" );
    }
    std::unique_ptr<icu::RegexPattern> rwscomma(
        icu::RegexPattern::compile( UNICODE_STRING_SIMPLE( R"(^[\s,]+$)" ) , 0 , status )
    );
    if ( U_FAILURE( status ) )
    {
        throw exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_COMPILE_FAILED , "rwscomma compile failed" );
    }
    std::unique_ptr<icu::RegexMatcher> rmatcher( rseparator -> matcher( __c_us_str , status ) );
    if ( U_FAILURE( status ) )
    {
        throw exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_MATCH_FAILED , "rseparator match failed" );
    }
    std::vector<icu::UnicodeString> words;
    if ( rmatcher -> find() )
    {
        int lpos = 0;
        for ( ; ; )
        {
            int bpos = rmatcher -> start( status );
            int epos = rmatcher -> end( status );
            if ( ( bpos == -1 ) || ( epos == -1 ) )
            {
                break;
            } // no more found
            int nxpos = ( rmatcher -> find() ) ? rmatcher -> start( status ) - 1
                                               : __c_us_str.length() - 1;
            // next pos
            std::unique_ptr<icu::RegexMatcher> rwscmachter(
                rwscomma -> matcher( __c_us_str.tempSubString( bpos , epos - bpos ) , status )
            );  // whitespace comma regex matcher
            if ( U_FAILURE( status ) )
            {
                throw exceptions::renarich_icu_error( RENA_ERR_ICU_REGEX_MATCH_FAILED , "rwscomma match failed" );
            }
            if ( ( rwscmachter -> matches( status ) ) &&
                 ( __c_us_str.tempSubString( lpos , bpos - lpos ).indexOf( '[' ) != -1 ) &&
                 ( __c_us_str.tempSubString( epos , nxpos - epos ).indexOf( ']' ) != -1 ) )
            {
                continue;
            } // treat as a color tag, no matter it is legal or not
            words.push_back( __c_us_str.tempSubString( lpos , epos - lpos ) );
            lpos = epos;
        }
        if ( lpos < __c_us_str.length() )
        {
            words.push_back( __c_us_str.tempSubString( lpos ) );
        }
    } // match
    else
    {
        words.push_back( __c_us_str );
    } // no match

    std::vector<token> tokens;
    for ( const auto& it : words )
    {
        std::string itstr;
        it.toUTF8String( itstr );
        token this_token = {};

        icu::UnicodeString ustr_no_ct = ustr_erase_ct( it );
        int ustr_no_ct_width = uswidth( ustr_no_ct );
        this_token._us_str = ustr_no_ct;
        this_token._i_width = ustr_no_ct_width;
        if ( ustr_no_ct == it )
        {
            this_token._v_cts = {};
        } // no color tag erased
        else
        {
            int i_no_ct = 0;
            for ( int i = 0 ; i < it.length() ; )
            {
                if ( it[i] != ustr_no_ct[i_no_ct] )
                {
                    int rbpos = it.indexOf( ']' , i );  // right bracket pos.
                    this_token._v_cts.push_back( { i_no_ct , it.tempSubString( i , rbpos - i + 1 ) } );
                    i = rbpos + 1;
                }
                else
                {
                    i++;
                    i_no_ct++;
                }
            }
        }

        tokens.push_back( this_token );
    }

    return tokens;
}

#endif // RENARICH_USE_ICU
