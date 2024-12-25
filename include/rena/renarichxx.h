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

namespace rena {

    __RENALIBS_API__ int rprintf( const char* __cp_c_format , ... );
    __RENALIBS_API__ int wrprintf( const wchar_t* __cp_wc_format , ... );

} // namespace rena

#endif // __RENALIBS_RENARICHXX_H__
