cmake_minimum_required(VERSION 3.12)
project(discord_bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
    add_compile_definitions(WIN32_LEAN_AND_MEAN=1)
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if (NOT DEFINED ENV{QTPATH})
    message(STATUS "QTPATH is not defined! Setting default path...")
    set(ENV{QTPATH} "C:/Qt/5.11.2/msvc2017_64")
endif()

add_subdirectory("ui")
add_subdirectory("libwinapi")
add_subdirectory("vendor/fmt" EXCLUDE_FROM_ALL)
