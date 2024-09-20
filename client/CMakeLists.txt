cmake_minimum_required(VERSION 3.30.3)

project("R-Type client")

include_directories(${PROJECT_SOURCE_DIR}/include)

include(../cmake/CPM.cmake)

# Add raylib package
CPMAddPackage("gh:raysan5/raylib#4.5.0")

add_executable(
    rtype_client
    Main.cpp
)

target_link_libraries(rtype_client raylib)
