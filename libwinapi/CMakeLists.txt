cmake_minimum_required(VERSION 3.12)
project(libwinapi LANGUAGES CXX)

# Determines if we are building the library as the master project
# or if we are included as a subdirectory.
set(MASTER_PROJECT ON)
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
   # If we are not the master project, then stop project configuration. The
    # rest of the options should be taken from the parent project.
    message(STATUS "Building libwinapi as children project...")

    # Create Library without setting up any variable. The master cmake
    # file should set up these variables.
    add_subdirectory(lib)
    set(MASTER_PROJECT OFF)
    return()
endif()

message(STATUS "Building libwinapi as main project...")

# If we are the master project, configure compilation flags.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
    add_compile_definitions(WIN32_LEAN_AND_MEAN=1)
else()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Create Library after we have set variables.
add_subdirectory(lib

# Enable testing
# option(LIBWINAPI_TESTS "Build tests" ON)
#
# if (LIBWINAPI_TESTS)
#	include(CTest)
#	enable_testing()
#   add_subdirectory(tests)
# endif()
