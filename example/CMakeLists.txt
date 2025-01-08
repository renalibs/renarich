add_executable(basic_usage
    ${CMAKE_CURRENT_SOURCE_DIR}/basic_usage.cpp
)
target_include_directories(basic_usage
    PUBLIC
        ${RENARICH_INCLUDE_DIR}
)

if(NOT ${RENARICH_HEADER_ONLY})

    add_executable(rprintf_usage
        ${CMAKE_CURRENT_SOURCE_DIR}/rprintf_usage.cpp
    )
    target_include_directories(rprintf_usage
        PUBLIC
            ${RENARICH_INCLUDE_DIR}
    )
    target_link_libraries(rprintf_usage
        renarich
    )

    add_executable(panel_usage
        ${CMAKE_CURRENT_SOURCE_DIR}/panel_usage.cpp
    )
    target_include_directories(panel_usage
        PUBLIC
            ${RENARICH_INCLUDE_DIR}
    )
    target_link_libraries(panel_usage
        renarich
    )

    add_executable(rstring_usage
        ${CMAKE_CURRENT_SOURCE_DIR}/rstring_usage.cpp
    )
    target_include_directories(rstring_usage
        PUBLIC
            ${RENARICH_INCLUDE_DIR}
    )
    target_link_libraries(rstring_usage
        renarich
    )

    if(WIN32)
        add_executable(wrprintf_usage
            ${CMAKE_CURRENT_SOURCE_DIR}/wrprintf_usage.cpp
        )
        target_include_directories(wrprintf_usage
            PUBLIC
                ${RENARICH_INCLUDE_DIR}
        )
        target_compile_options(wrprintf_usage
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        )
        target_link_libraries(wrprintf_usage
            renarich
        )

        add_executable(wpanel_usage
            ${CMAKE_CURRENT_SOURCE_DIR}/wpanel_usage.cpp
        )
        target_include_directories(wpanel_usage
            PUBLIC
                ${RENARICH_INCLUDE_DIR}
        )
        target_compile_options(wpanel_usage
            PRIVATE
                $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        )
        target_link_libraries(wpanel_usage
            renarich
        )
    endif()
    # these wide modules' examples are only for windows

endif()
