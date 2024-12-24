add_executable(basic_usage
    ${CMAKE_CURRENT_SOURCE_DIR}/basic_usage.cpp
)
target_include_directories(basic_usage
    PUBLIC
        ${RENARICH_INCLUDE_DIR}
)
