cmake_minimum_required(VERSION 3.12)
project(libwinapi LANGUAGES CXX)

# Determines if we are building the library as the master project
# or if we are included as a subdirectory.
set(MASTER_PROJECT ON)
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    # If we are not the master project, then stop project configuration. The
    # rest of the options should be taken from the parent project.
    message(STATUS "Building libwinapi as children project...")
    set(MASTER_PROJECT OFF)

    # Create Library without setting up any variable. The master cmake
    # file should set up these variables.
    add_subdirectory(lib)
    return()
endif()

message(STATUS "Building libwinapi as main project...")

# If we are the master project, configure compilation flags.
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

# Must be changed to use FindPackage or something.
get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}" DIRECTORY)
set(EXPECTED_INCLUDE_PATH "${PARENT_DIR}/vendor/expected/include")

# Create Library after we have set variables.
add_subdirectory(lib)

# Enable testing
option(LIBWINAPI_TESTS "Build tests" ON)

if (LIBWINAPI_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
