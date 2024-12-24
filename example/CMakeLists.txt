add_executable(basic_usage
    ${CMAKE_CURRENT_SOURCE_DIR}/basic_usage.cpp
)
target_include_directories(basic_usage
    PUBLIC
        ${RENARICH_INCLUDE_DIR}
)

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
