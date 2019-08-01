cmake_minimum_required(VERSION 3.12)
project(discord_bot_ui LANGUAGES CXX)

add_executable(app
    WIN32
        main.cpp
)

target_include_directories(app
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(app
    PRIVATE
    general
        "fmt-header-only"
)
