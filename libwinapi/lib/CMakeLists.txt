cmake_minimum_required(VERSION 3.12)
project(winapi LANGUAGES CXX)

add_library(libwinapi
    SHARED
        lib.cpp
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
