cmake_minimum_required(VERSION 3.27)
project("R-Type client")

add_executable(r-type_client
    Main.cpp
    src/Client.cpp
)

target_link_directories(
    r-type_client PUBLIC
    "../Libs/Graphics"
    "../Libs/Network"
)

target_link_libraries(
    r-type_client PUBLIC
    Network
    Graphics
)

target_include_directories(
    r-type_client PUBLIC
    "include"
)
