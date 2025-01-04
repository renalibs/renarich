cmake_minimum_required(VERSION 3.19)

set(ICU4C_PKG_URL "https://github.com/renalibs/icu4c_bin/raw/refs/heads/main/76_1/")
set(ICU4C_PKG_HASH "")
set(ICU4C_PKG_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/_deps/")
set(ICU4C_PKG_PATH "${ICU4C_PKG_DOWNLOAD_DIR}/icu4c_76_1")
set(ICU4C_BIN_DIR "${ICU4C_PKG_DOWNLOAD_DIR}/icu4c")

if(WIN32)
    string(APPEND ICU4C_PKG_URL "WIN64/")
    if(MSVC)
        string(APPEND ICU4C_PKG_URL "MSVC2022.zip")
        set(ICU4C_PKG_HASH "fa0e41b9f891904f78eba63bd9bb1034322e79029e300068059477a97b438903")
    elseif(MINGW)
        string(APPEND ICU4C_PKG_URL "MinGW.zip")
        set(ICU4C_PKG_HASH "1615558bc305fa9316385a3ff15cf996778e41139f9ab5c070a2ac0c0b4aaa0e")
    else()
        message(FATAL_ERROR "Only MSVC and MinGW are supported under Windows.")
    endif()
    string(APPEND ICU4C_PKG_PATH ".zip")
elseif(UNIX)
    string(APPEND ICU4C_PKG_URL "Linux/GCC.tar.gz")
    string(APPEND ICU4C_PKG_PATH ".tar.gz")
    set(ICU4C_PKG_HASH "3d1d5e68fb58a462df1d80c7ce4c836b8dfb14e63851cad76cdfe88b914d6208")
elseif(APPLE)
    string(APPEND ICU4C_PKG_URL "MacOS/Clang.tar.gz")
    string(APPEND ICU4C_PKG_PATH ".tar.gz")
    set(ICU4C_PKG_HASH "06c7dfd0f8065d68c52efbfc876e166c4ca295ca06fb3d47109aa0b08448a025")
else()
    message(FATAL_ERROR "Other platforms except Windows, Unix-like or MacOS are not supported.")
endif()

if(EXISTS ${ICU4C_BIN_DIR})
    file(REMOVE_RECURSE ${ICU4C_BIN_DIR})
endif()

message(STATUS "Fetching ICU4C binary package from: ${ICU4C_PKG_URL}.")
file(MAKE_DIRECTORY ${ICU4C_PKG_DOWNLOAD_DIR})
file(DOWNLOAD ${ICU4C_PKG_URL}
    ${ICU4C_PKG_PATH}
    TIMEOUT 60
    STATUS DOWNLOAD_STATUS
    EXPECTED_HASH SHA256=${ICU4C_PKG_HASH}
)
list(GET DOWNLOAD_STATUS 0 DOWNLOAD_STATUS_CODE)
list(GET DOWNLOAD_STATUS 1 DOWNLOAD_STATUS_MSG)
if(${DOWNLOAD_STATUS_CODE} EQUAL 0)
    message(STATUS "Download completed und succeeded.")
else()
    message(FATAL_ERROR "Download failed: ${DOWNLOAD_STATUS_MSG} (${DOWNLOAD_STATUS_CODE})")
endif()

message(STATUS "Extracting ICU4C binary package...")
file(MAKE_DIRECTORY ${ICU4C_BIN_DIR})
if(WIN32)
    execute_process(
        COMMAND powershell -Command Expand-Archive -Path ${ICU4C_PKG_PATH} -DestinationPath ${ICU4C_BIN_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
    if(MSVC)
        set(ICU4C_ROOT_DIR "${ICU4C_BIN_DIR}/MSVC2022" CACHE STRING INTERNAL)
        set(ICU4C_LIB_BIN_DIR "${ICU4C_ROOT_DIR}/bin64")
        set(ICU4C_LIB_LIB_DIR "${ICU4C_ROOT_DIR}/lib64")
        set(ICU4C_INCLUDE_DIR "${ICU4C_ROOT_DIR}/include" CACHE STRING INTERNAL)
        set(ICU4C_LIB_DATA "${ICU4C_LIB_LIB_DIR}/icudt.lib" CACHE STRING INTERNAL)
        set(ICU4C_LIB_COMMON "${ICU4C_LIB_LIB_DIR}/icuuc.lib" CACHE STRING INTERNAL)
        set(ICU4C_LIB_I18N "${ICU4C_LIB_LIB_DIR}/icuin.lib" CACHE STRING INTERNAL)
        set(ICU4C_LIB_IO "${ICU4C_LIB_LIB_DIR}/icuio.lib" CACHE STRING INTERNAL)
        set(ICU4C_LIB_TOOL_UTILS "${ICU4C_LIB_LIB_DIR}/icutu.lib" CACHE STRING INTERNAL)
    else()
        set(ICU4C_ROOT_DIR "${ICU4C_BIN_DIR}/MinGW" CACHE STRING INTERNAL)
        set(ICU4C_LIB_BIN_DIR "${ICU4C_ROOT_DIR}/bin")
        set(ICU4C_LIB_LIB_DIR "${ICU4C_ROOT_DIR}/lib")
        set(ICU4C_INCLUDE_DIR "${ICU4C_ROOT_DIR}/include" CACHE STRING INTERNAL)
        set(ICU4C_LIB_DATA "${ICU4C_LIB_BIN_DIR}/icudt76.dll" CACHE STRING INTERNAL)
        set(ICU4C_LIB_COMMON "${ICU4C_LIB_BIN_DIR}/icuuc76.dll" CACHE STRING INTERNAL)
        set(ICU4C_LIB_I18N "${ICU4C_LIB_BIN_DIR}/icuin76.dll" CACHE STRING INTERNAL)
        set(ICU4C_LIB_IO "${ICU4C_LIB_BIN_DIR}/icuio76.dll" CACHE STRING INTERNAL)
        set(ICU4C_LIB_TOOL_UTILS "${ICU4C_LIB_BIN_DIR}/icutu76.dll" CACHE STRING INTERNAL)
    endif()
    set(ICU4C_LIB_DATA_FILE_LIST
        "${ICU4C_LIB_BIN_DIR}/icudt76.dll"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_COMMON_FILE_LIST
        "${ICU4C_LIB_BIN_DIR}/icuuc76.dll"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_I18N_FILE_LIST
        "${ICU4C_LIB_BIN_DIR}/icuin76.dll"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_IO_FILE_LIST
        "${ICU4C_LIB_BIN_DIR}/icuio76.dll"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_TOOL_UTILS_FILE_LIST
        "${ICU4C_LIB_BIN_DIR}/icutu76.dll"
    CACHE STRING INTERNAL)
else()
    execute_process(
        COMMAND tar -zxf ${ICU4C_PKG_PATH} -C ${ICU4C_BIN_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
    if(UNIX)
        set(ICU4C_ROOT_DIR "${ICU4C_BIN_DIR}/GCC" CACHE STRING INTERNAL)
        set(PLATFORM_DLL_EXT "so")
    else()
        set(ICU4C_ROOT_DIR "${ICU4C_BIN_DIR}/Clang" CACHE STRING INTERNAL)
        set(PLATFORM_DLL_EXT "dylib")
    endif()
    set(ICU4C_INCLUDE_DIR "${ICU4C_ROOT_DIR}/include" CACHE STRING INTERNAL)
    set(ICU4C_LIB_DATA "${ICU4C_ROOT_DIR}/lib/libicudata.${PLATFORM_DLL_EXT}" CACHE STRING INTERNAL)
    set(ICU4C_LIB_DATA_FILE_LIST
        "${ICU4C_ROOT_DIR}/lib/libicudata.${PLATFORM_DLL_EXT}"
        "${ICU4C_ROOT_DIR}/lib/libicudata.${PLATFORM_DLL_EXT}.76"
        "${ICU4C_ROOT_DIR}/lib/libicudata.${PLATFORM_DLL_EXT}.76.1"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_COMMON "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}" CACHE STRING INTERNAL)
    set(ICU4C_LIB_COMMON_FILE_LIST
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}"
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}.76"
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}.76.1"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_I18N "${ICU4C_ROOT_DIR}/lib/libicui18n.${PLATFORM_DLL_EXT}" CACHE STRING INTERNAL)
    set(ICU4C_LIB_I18N_FILE_LIST
        "${ICU4C_ROOT_DIR}/lib/libicui18n.${PLATFORM_DLL_EXT}"
        "${ICU4C_ROOT_DIR}/lib/libicui18n.${PLATFORM_DLL_EXT}.76"
        "${ICU4C_ROOT_DIR}/lib/libicui18n.${PLATFORM_DLL_EXT}.76.1"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_IO "${ICU4C_ROOT_DIR}/lib/libicuio.${PLATFORM_DLL_EXT}" CACHE STRING INTERNAL)
    set(ICU4C_LIB_IO_FILE_LIST
        "${ICU4C_ROOT_DIR}/lib/libicuio.${PLATFORM_DLL_EXT}"
        "${ICU4C_ROOT_DIR}/lib/libicuio.${PLATFORM_DLL_EXT}.76"
        "${ICU4C_ROOT_DIR}/lib/libicuio.${PLATFORM_DLL_EXT}.76.1"
    CACHE STRING INTERNAL)
    set(ICU4C_LIB_TOOL_UTILS "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}" CACHE STRING INTERNAL)
    set(ICU4C_LIB_TOOL_UTILS_FILE_LIST
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}"
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}.76"
        "${ICU4C_ROOT_DIR}/lib/libicuuc.${PLATFORM_DLL_EXT}.76.1"
    CACHE STRING INTERNAL)
endif()
message(STATUS "Extract completed.")
