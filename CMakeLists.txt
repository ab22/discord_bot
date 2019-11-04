cmake_minimum_required(VERSION 3.12)
project(discord_bot LANGUAGES CXX)

include(GNUInstallDirs)

message(STATUS "Install lib dir: ${CMAKE_INSTALL_LIBDIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    add_compile_options(/W4 /w44265 /w44061 /w44062)
    add_compile_definitions(WIN32_LEAN_AND_MEAN=1)
elseif (GNU OR Clang)
    add_compile_options(-Wall -Wextra -Wunreachable-code -Wpedantic)
endif()

set(EXPECTED_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/vendor/expected/include")
set(UWEBSOCKET_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/vendor/uWebSockets/src")
set(USOCKETS_LIB_PATH "${CMAKE_SOURCE_DIR}/vendor/uWebSockets/uSockets/x64/Release")

add_subdirectory("ui")
add_subdirectory("libwinapi")
add_subdirectory("libdiscord")
add_subdirectory("vendor/fmt" EXCLUDE_FROM_ALL)
