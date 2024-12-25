#include"color_tag.h"

#include<algorithm>
#include<unordered_set>

const std::unordered_set<std::string> legal_color_tag_set = {
    "/" ,
    "//" ,
    "black" ,
    "red" ,
    "green" ,
    "yellow" ,
    "blue" ,
    "magenta",
    "cyan" ,
    "white" ,
    "gray" ,
    "brightred" ,
    "brightgreen" ,
    "brightyellow" ,
    "brightblue" ,
    "brightmagenta" ,
    "brightcyan" ,
    "brightwhite" ,
    "bblack" ,
    "bred" ,
    "bgreen" ,
    "byellow" ,
    "bblue" ,
    "bmagenta" ,
    "bcyan" ,
    "bwhite" ,
    "bgray" ,
    "bbrightred" ,
    "bbrightgreen" ,
    "bbrightyellow" ,
    "bbrightblue" ,
    "bbrightmagenta" ,
    "bbrightcyan" ,
    "bbrightwhite" ,
#ifdef RENARICH_USE_ANSI
    "bold" ,
    "dim" ,
    "italic" ,
    "underline" ,
    "overline" ,
    "strike" ,
    "reverse" ,
#endif // RENARICH_USE_ANSI
};

bool rena::builtin::is_legal_color_tag( const std::string& __c_s_tag ){
    return ( legal_color_tag_set.find( __c_s_tag ) != legal_color_tag_set.end() );
}

rena::color_code rena::builtin::parse_color_tag( const std::string& __c_s_tag ){
    std::string tag = __c_s_tag;
    std::transform( tag.begin() , tag.end() , tag.begin() , []( unsigned char __u8i_c ){
        return std::tolower( __u8i_c );
    } );
    // tolower
    auto nstart = std::find_if_not( tag.begin() , tag.end() , ::isspace );
    auto nend = std::find_if_not( tag.rbegin() , tag.rend() , ::isspace ).base();
    tag = ( nstart < nend ) ? std::string( nstart , nend ) : "";
    if ( tag.empty() )
    {
        return IllegalColorTag;
    } // empty tag
    // trim

    if ( tag == "/" ) { return PopColorTag; }
    else if ( tag == "//" ) { return PopAllColorTag; }
    else if ( tag == "black" ) { return fcolor::BLACK; }
    else if ( tag == "red" ) { return fcolor::RED; }
    else if ( tag == "green" ) { return fcolor::GREEN; }
    else if ( tag == "yellow" ) { return fcolor::YELLOW; }
    else if ( tag == "blue" ) { return fcolor::BLUE; }
    else if ( tag == "magenta" ) { return fcolor::MAGENTA; }
    else if ( tag == "cyan" ) { return fcolor::CYAN; }
    else if ( tag == "white" ) { return fcolor::WHITE; }
    else if ( tag == "gray" ) { return fcolor::GRAY; }
    else if ( tag == "brightred" ) { return fcolor::BRIGHTRED; }
    else if ( tag == "brightgreen" ) { return fcolor::BRIGHTGREEN; }
    else if ( tag == "brightyellow" ) { return fcolor::BRIGHTYELLOW; }
    else if ( tag == "brightblue" ) { return fcolor::BRIGHTBLUE; }
    else if ( tag == "brightmagenta" ) { return fcolor::BRIGHTMAGENTA; }
    else if ( tag == "brightcyan" ) { return fcolor::BRIGHTCYAN; }
    else if ( tag == "brightwhite" ) { return fcolor::BRIGHTWHITE; }
    else if ( tag == "bblack" ) { return bcolor::BLACK; }
    else if ( tag == "bred" ) { return bcolor::RED; }
    else if ( tag == "bgreen" ) { return bcolor::GREEN; }
    else if ( tag == "byellow" ) { return bcolor::YELLOW; }
    else if ( tag == "bblue" ) { return bcolor::BLUE; }
    else if ( tag == "bmagenta" ) { return bcolor::MAGENTA; }
    else if ( tag == "bcyan" ) { return bcolor::CYAN; }
    else if ( tag == "bwhite" ) { return bcolor::WHITE; }
    else if ( tag == "bgray" ) { return bcolor::GRAY; }
    else if ( tag == "bbrightred" ) { return bcolor::BRIGHTRED; }
    else if ( tag == "bbrightgreen" ) { return bcolor::BRIGHTGREEN; }
    else if ( tag == "bbrightyellow" ) { return bcolor::BRIGHTYELLOW; }
    else if ( tag == "bbrightblue" ) { return bcolor::BRIGHTBLUE; }
    else if ( tag == "bbrightmagenta" ) { return bcolor::BRIGHTMAGENTA; }
    else if ( tag == "bbrightcyan" ) { return bcolor::BRIGHTCYAN; }
    else if ( tag == "bbrightwhite" ) { return bcolor::BRIGHTWHITE; }
#ifdef RENARICH_USE_ANSI
    else if ( tag == "bold" ) { return fstyle::BOLD; }
    else if ( tag == "dim" ) { return fstyle::DIM; }
    else if ( tag == "italic" ) { return fstyle::ITALIC; }
    else if ( tag == "underline" ) { return fstyle::UNDERLINE; }
    else if ( tag == "overline" ) { return fstyle::OVERLINE; }
    else if ( tag == "strike" ) { return fstyle::STRIKE; }
    else if ( tag == "reverse" ) { return fstyle::REVERSE; }
#endif // RENARICH_USE_ANSI
    else {}

    return IllegalColorTag;
}
