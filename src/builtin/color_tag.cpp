#include"color_tag.h"

#include<algorithm>
#include<cwctype>
#include<unordered_map>

template<class _CharT>
using color_tag_map = std::unordered_map<std::basic_string<_CharT>,rena::color_code>;

const color_tag_map<char> legal_color_tag_map = {
    { "/" , rena::builtin::PopColorTag } ,
    { "//" , rena::builtin::PopAllColorTag } ,
    { "black" , rena::fcolor::BLACK } ,
    { "red" , rena::fcolor::RED } ,
    { "green" , rena::fcolor::GREEN } ,
    { "yellow" , rena::fcolor::YELLOW } ,
    { "blue" , rena::fcolor::BLUE } ,
    { "magenta" , rena::fcolor::MAGENTA } , 
    { "cyan" , rena::fcolor::CYAN } ,
    { "white" , rena::fcolor::WHITE } ,
    { "gray" , rena::fcolor::GRAY } ,
    { "brightred" , rena::fcolor::BRIGHTRED } ,
    { "brightgreen" , rena::fcolor::BRIGHTGREEN } ,
    { "brightyellow" , rena::fcolor::BRIGHTYELLOW } ,
    { "brightblue" , rena::fcolor::BRIGHTBLUE } ,
    { "brightmagenta" , rena::fcolor::BRIGHTMAGENTA } ,
    { "brightcyan" , rena::fcolor::BRIGHTCYAN } ,
    { "brightwhite" , rena::fcolor::BRIGHTWHITE } ,
    { "bblack" , rena::bcolor::BLACK } ,
    { "bred" , rena::bcolor::RED } ,
    { "bgreen" , rena::bcolor::GREEN } ,
    { "byellow" , rena::bcolor::YELLOW } ,
    { "bblue" , rena::bcolor::BLUE } ,
    { "bmagenta" , rena::bcolor::MAGENTA } ,
    { "bcyan" , rena::bcolor::CYAN } ,
    { "bwhite" , rena::bcolor::WHITE } ,
    { "bgray" , rena::bcolor::GRAY } ,
    { "bbrightred" , rena::bcolor::BRIGHTRED } ,
    { "bbrightgreen" , rena::bcolor::BRIGHTGREEN } ,
    { "bbrightyellow" , rena::bcolor::BRIGHTYELLOW } ,
    { "bbrightblue" , rena::bcolor::BRIGHTBLUE } ,
    { "bbrightmagenta" , rena::bcolor::BRIGHTMAGENTA } ,
    { "bbrightcyan" , rena::bcolor::BRIGHTCYAN } ,
    { "bbrightwhite" , rena::bcolor::BRIGHTWHITE } ,
#ifdef RENARICH_USE_ANSI
    { "bold" , rena::fstyle::BOLD } ,
    { "dim" , rena::fstyle::DIM } ,
    { "italic" , rena::fstyle::ITALIC } ,
    { "underline" , rena::fstyle::UNDERLINE } ,
    { "overline" , rena::fstyle::OVERLINE } ,
    { "strike" , rena::fstyle::STRIKE } ,
    { "reverse" , rena::fstyle::REVERSE } ,
#endif // RENARICH_USE_ANSI
};

const color_tag_map<wchar_t> legal_color_tag_map_w = {
    { L"/" , rena::builtin::PopColorTag } ,
    { L"//" , rena::builtin::PopAllColorTag } ,
    { L"black" , rena::fcolor::BLACK } ,
    { L"red" , rena::fcolor::RED } ,
    { L"green" , rena::fcolor::GREEN } ,
    { L"yellow" , rena::fcolor::YELLOW } ,
    { L"blue" , rena::fcolor::BLUE } ,
    { L"magenta" , rena::fcolor::MAGENTA } , 
    { L"cyan" , rena::fcolor::CYAN } ,
    { L"white" , rena::fcolor::WHITE } ,
    { L"gray" , rena::fcolor::GRAY } ,
    { L"brightred" , rena::fcolor::BRIGHTRED } ,
    { L"brightgreen" , rena::fcolor::BRIGHTGREEN } ,
    { L"brightyellow" , rena::fcolor::BRIGHTYELLOW } ,
    { L"brightblue" , rena::fcolor::BRIGHTBLUE } ,
    { L"brightmagenta" , rena::fcolor::BRIGHTMAGENTA } ,
    { L"brightcyan" , rena::fcolor::BRIGHTCYAN } ,
    { L"brightwhite" , rena::fcolor::BRIGHTWHITE } ,
    { L"bblack" , rena::bcolor::BLACK } ,
    { L"bred" , rena::bcolor::RED } ,
    { L"bgreen" , rena::bcolor::GREEN } ,
    { L"byellow" , rena::bcolor::YELLOW } ,
    { L"bblue" , rena::bcolor::BLUE } ,
    { L"bmagenta" , rena::bcolor::MAGENTA } ,
    { L"bcyan" , rena::bcolor::CYAN } ,
    { L"bwhite" , rena::bcolor::WHITE } ,
    { L"bgray" , rena::bcolor::GRAY } ,
    { L"bbrightred" , rena::bcolor::BRIGHTRED } ,
    { L"bbrightgreen" , rena::bcolor::BRIGHTGREEN } ,
    { L"bbrightyellow" , rena::bcolor::BRIGHTYELLOW } ,
    { L"bbrightblue" , rena::bcolor::BRIGHTBLUE } ,
    { L"bbrightmagenta" , rena::bcolor::BRIGHTMAGENTA } ,
    { L"bbrightcyan" , rena::bcolor::BRIGHTCYAN } ,
    { L"bbrightwhite" , rena::bcolor::BRIGHTWHITE } ,
#ifdef RENARICH_USE_ANSI
    { L"bold" , rena::fstyle::BOLD } ,
    { L"dim" , rena::fstyle::DIM } ,
    { L"italic" , rena::fstyle::ITALIC } ,
    { L"underline" , rena::fstyle::UNDERLINE } ,
    { L"overline" , rena::fstyle::OVERLINE } ,
    { L"strike" , rena::fstyle::STRIKE } ,
    { L"reverse" , rena::fstyle::REVERSE } ,
#endif // RENARICH_USE_ANSI
};

template<class _CharT>
bool _is_space( _CharT __c ){
    if constexpr ( std::is_same_v<_CharT,wchar_t> )
    {
        return std::iswspace( __c );
    }
    else
    {
        return std::isspace( __c );
    }
}

template<class _CharT>
rena::color_code rena::builtin::parse_color_tag( const std::basic_string<_CharT>& __c_s_tag ){
    using _string = std::basic_string<_CharT>;

    _string tag = __c_s_tag;
    constexpr bool is_wchar_mode = ( std::is_same_v<_CharT,wchar_t> );

    std::transform( tag.begin() , tag.end() , tag.begin() , [is_wchar_mode]( _CharT __c ) -> _CharT {
        return ( is_wchar_mode ) ? std::towlower( __c ) : std::tolower( __c );
    } );
    // tolower

    auto nstart = std::find_if_not( tag.begin() , tag.end() , _is_space<_CharT> );
    auto nend = std::find_if_not( tag.rbegin() , tag.rend() , _is_space<_CharT> ).base();
    tag = ( nstart < nend ) ? _string( nstart , nend ) : _string();
    if ( tag.empty() )
    {
        return IllegalColorTag;
    } // empty tag
    // trim
    
    color_code code;
    if constexpr ( is_wchar_mode )
    {
        if ( legal_color_tag_map_w.find( tag ) != legal_color_tag_map_w.end() )
        {
            code = legal_color_tag_map_w.at( tag );
        }
        else
        {
            code = IllegalColorTag;
        }
        
    }
    else
    {
        if ( legal_color_tag_map.find( tag ) != legal_color_tag_map.end() )
        {
            code = legal_color_tag_map.at( tag );
        }
        else
        {
            code = IllegalColorTag;
        }
    }

    return code;
}

template rena::color_code rena::builtin::parse_color_tag<char>( const std::string& );
template rena::color_code rena::builtin::parse_color_tag<wchar_t>( const std::wstring& );
