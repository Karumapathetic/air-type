cmake_minimum_required(VERSION 3.27)
project("R-Type server")


add_executable(r-type_server
    Main.cpp
    src/Server.cpp
)

target_link_directories(
    r-type_server PUBLIC
    "../Libs/ECS"
    "../Libs/Network"
)

target_link_libraries(
    r-type_server PUBLIC
    ECS
    Network
)

target_include_directories(
    r-type_server PUBLIC
    "include"
)
