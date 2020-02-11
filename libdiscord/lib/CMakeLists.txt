cmake_minimum_required(VERSION 3.12)
project(discord-api LANGUAGES CXX)

# Find Boost
set(Boost_USE_STATIC_LIBS    ON)
set(Boost_USE_DEBUG_LIBS     ON)
set(Boost_USE_RELEASE_LIBS   ON)
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71
    COMPONENTS
        system
        date_time
    REQUIRED
)

message(STATUS "Boost Include Path: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost Library Path: ${Boost_LIBRARY_DIRS}")

# Find OpenSSL
set(OPENSSL_ROOT_DIR        "C:/Users/amendoza/cpp/openssl")
set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

message(STATUS "OpenSSL Path: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL Library: ${OPENSSL_SSL_LIBRARY} ${OPENSSL_VERSION}")
message(STATUS "OpenSSL Use Static Libs: ${OPENSSL_USE_STATIC_LIBS}")

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (NOT DEFINED EXPECTED_INCLUDE_PATH)
    message (FATAL_ERROR "tl::expected include path not found!")
endif()

add_library(libdiscord
    SHARED
        lib.cpp
)

set_target_properties(libdiscord
    PROPERTIES
        VERSION 1
        SOVERSION 1
        PUBLIC_HEADER "include/libdiscord/lib.hpp"
        C_EXTENSIONS OFF
        CXX_EXTENSIONS OFF
)

target_include_directories(libdiscord
    PUBLIC
        "${EXPECTED_INCLUDE_PATH}"
        "${Boost_INCLUDE_DIRS}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/../include/"
)

target_link_libraries(libdiscord
    PRIVATE
    general
        Boost::system
        Boost::date_time
        OpenSSL::SSL
        "fmt-header-only"
)

if (MSVC)
    target_compile_definitions(libdiscord
        PRIVATE
            WIN32_LEAN_AND_MEAN
            WIN_EXPORT
            _WIN32_WINNT=0x0601
    )
endif()
