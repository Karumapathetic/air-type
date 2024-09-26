cmake_minimum_required(VERSION 3.27)
project("R-Type client")

add_executable(r-type_client
    Main.cpp
)

target_link_directories(
    r-type_client PUBLIC
    "../Libs/ECS"
    "../Libs/Network"
    "../Libs/Graphics"
)

target_link_libraries(
    r-type_client PUBLIC
    ECS
    Network
    Graphics
    raylib
)

target_include_directories(
    r-type_client PUBLIC
    "include"
)
