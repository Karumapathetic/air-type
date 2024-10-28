cmake_minimum_required(VERSION 3.27)
project("R-Type Network Lib")

add_library(Network INTERFACE)

target_include_directories(
    Network INTERFACE
    "include"
    "../../3rdParties/asio/asio/include"
)
