cmake_minimum_required(VERSION 3.27)
project("R-Type Graphics Lib")

add_library(
    Graphics STATIC
    LaunchGame.cpp
    src/DrawGame.cpp
    src/DrawMenu.cpp
)

target_include_directories(
    Graphics PUBLIC
    "include"
)

target_link_libraries(
    Graphics
    raylib
    ECS
)
