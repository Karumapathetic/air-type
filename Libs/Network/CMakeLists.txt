add_library(
    Network STATIC
    src/UDPClient.cpp
    src/UDPServer.cpp
)

target_include_directories(
    Network PUBLIC
    "include"
)