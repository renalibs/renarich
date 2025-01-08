#include"ucwidth.h"

#include"unicode/uchar.h"

int rena::builtin::ucwidth( UChar32 __c32_uc ){
    int ea_width = u_getIntPropertyValue( __c32_uc , UCHAR_EAST_ASIAN_WIDTH );
    if ( ( ea_width == U_EA_FULLWIDTH ) || ( ea_width == U_EA_WIDE ) )
    {
        return 2;
    }
    return 1;
}

int rena::builtin::uswidth( const icu::UnicodeString& __c_us_str ){
    int width = 0;
    for ( int i = 0 ; i < __c_us_str.length() ; i++ )
    {
        width += ucwidth( __c_us_str.char32At( i ) );
    }
    return width;
}
