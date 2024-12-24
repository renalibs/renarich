#include"color_tag.h"

#include<algorithm>

rena::_color_code rena::builtin::parse_color_tag( const std::string& __c_s_tag ){
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
    
    return IllegalColorTag;
}
