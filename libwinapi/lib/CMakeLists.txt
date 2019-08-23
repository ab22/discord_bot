cmake_minimum_required(VERSION 3.12)
project(winapi LANGUAGES CXX)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(libwinapi
    SHARED
        v1/core/errors.cpp
        v1/internal/winapi.cpp
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
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)
