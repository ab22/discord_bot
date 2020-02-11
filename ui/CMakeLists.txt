cmake_minimum_required(VERSION 3.12)
project(ui LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
    set(CMAKE_PREFIX_PATH $ENV{QT5_PATH64})
else()
    set(CMAKE_PREFIX_PATH $ENV{QT5_PATH})
endif()

message(STATUS "Qt5 Dir: ${CMAKE_PREFIX_PATH}")

if (NOT DEFINED EXPECTED_INCLUDE_PATH)
    message (FATAL_ERROR "tl::expected include path not found!")
endif()

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5
    COMPONENTS
        Widgets
        Core
        Gui
    REQUIRED
)

add_executable(ui
    main.cpp
    mainwindow.cpp
    mainwindow.h

    themes/qdarkstyle/style.qrc
    themes/breeze/breeze.qrc
    themes/dark-orange.qrc
)

target_include_directories(ui
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/libwinapi/include"
        "${CMAKE_SOURCE_DIR}/libdiscord/include"
        "${EXPECTED_INCLUDE_PATH}"
)

target_link_libraries(ui
    PRIVATE
    general
        libwinapi
        libdiscord
        "fmt-header-only"
        Qt5::Widgets
)

if (WIN32)
    add_custom_command(
        TARGET
            ui
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:Qt5::Widgets>
                $<TARGET_FILE:Qt5::Core>
                $<TARGET_FILE:Qt5::Gui>
                ...
            $<TARGET_FILE_DIR:ui>
    )
endif()
