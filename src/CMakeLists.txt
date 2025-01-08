if(${RENARICH_USE_ICU})
    include(${PROJECT_SOURCE_DIR}/cmake/icu4c_dep.cmake)
endif()

add_library(renarich SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/builtin/box_chars.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/builtin/color_tag.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/builtin/console_helper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/builtin/nwrprintf.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/builtin/nwstrcvt.cpp
    $<$<BOOL:${RENARICH_USE_ICU}>:${CMAKE_CURRENT_SOURCE_DIR}/builtin/tokenize.cpp>
    $<$<BOOL:${RENARICH_USE_ICU}>:${CMAKE_CURRENT_SOURCE_DIR}/builtin/ucwidth.cpp>
    $<$<NOT:$<BOOL:${RENARICH_USE_ICU}>>:${CMAKE_CURRENT_SOURCE_DIR}/builtin/wcwidth_noicu.cpp>
    $<$<BOOL:${RENARICH_USE_ICU}>:${CMAKE_CURRENT_SOURCE_DIR}/builtin/wcwidth.cpp>
    ${CMAKE_CURRENT_SOURCE_DIR}/basic_rcc.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/panel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/renarichxx_cfg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rprintf.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/rstring.cpp
)
target_include_directories(renarich
    PUBLIC
        ${RENARICH_INCLUDE_DIR}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        $<$<BOOL:${RENARICH_USE_ICU}>:${ICU4C_INCLUDE_DIR}>
)
target_compile_definitions(renarich
    PUBLIC
        $<$<BOOL:${RENARICH_USE_ICU}>:RENARICH_USE_ICU>
    PRIVATE
        __RENALIBS_EXPORT__
        $<$<PLATFORM_ID:Windows>:UNICODE>
        $<$<PLATFORM_ID:Windows>:_UNICODE>
)
target_compile_options(renarich
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
)
if(${RENARICH_USE_ICU})
    target_link_libraries(renarich
        ${ICU4C_LIB_DATA}
        ${ICU4C_LIB_COMMON}
        ${ICU4C_LIB_I18N}
    )
    add_custom_command(TARGET renarich POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${ICU4C_LIB_DATA_FILE_LIST} ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${ICU4C_LIB_COMMON_FILE_LIST} ${LIBRARY_OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy ${ICU4C_LIB_I18N_FILE_LIST} ${LIBRARY_OUTPUT_PATH}
        COMMENT "Copying ICU4C denpendency to CMake library output directory"
    )
endif()
