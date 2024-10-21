cmake_minimum_required(VERSION 3.27)
project("R-Type Network Lib")

add_library(
    Network STATIC
    src/UDPClient.cpp
    src/UDPServer.cpp
    src/BinaryBuffer.cpp
)

target_include_directories(
    Network PUBLIC
    "include"
    "../../3rdParties/asio/asio/include"
)
