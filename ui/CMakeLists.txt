cmake_minimum_required(VERSION 3.12)
project(ui LANGUAGES CXX)

function(copy_qt_dll dll_path)
    add_custom_command(
        TARGET
            discord_bot
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
                ${dll_path}
                $<TARGET_FILE_DIR:discord_bot>
    )
endfunction()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORRC ON)
set(CMAKE_AUTOUIC ON)

if (DEFINED ENV{QTPATH})
    set(CMAKE_PREFIX_PATH ENV{QTPATH})
else()
    message("-- QTPATH is not defined!")
    message("-- Using default Qt path...")
    set(CMAKE_PREFIX_PATH "C:/Qt/5.11.2/msvc2017_64")
endif()

message("-- QTPATH: ${CMAKE_PREFIX_PATH}")

if (CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(discord_bot
    WIN32
        main.cpp
        mainwindow.cpp
        mainwindow.h
)

target_include_directories(discord_bot
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(discord_bot
    PRIVATE
    general
        "fmt-header-only"
        Qt5::Widgets
)

if (WIN32)
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll")
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Cored.dll")
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Gui.dll")
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Guid.dll")
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Widgets.dll")
    copy_qt_dll("${CMAKE_PREFIX_PATH}/bin/Qt5Widgetsd.dll")
endif()
