cmake_minimum_required(VERSION 3.12)
project(winapi LANGUAGES CXX)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (NOT DEFINED EXPECTED_INCLUDE_PATH)
    message (FATAL_ERROR "tl::expected include path not found!")
endif()

add_library(libwinapi
    SHARED
        core/errors.cpp
        internal/winapi.cpp
)

set_target_properties(libwinapi
    PROPERTIES
        VERSION 1
        SOVERSION 1
        PUBLIC_HEADER "include/libwinapi/lib.hpp"
        C_EXTENSIONS OFF
        CXX_EXTENSIONS OFF
)

target_include_directories(libwinapi
    PUBLIC
        "${EXPECTED_INCLUDE_PATH}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)


if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_definitions(libwinapi
        PRIVATE
            WIN32_LEAN_AND_MEAN
            WIN_EXPORT
    )
endif()
