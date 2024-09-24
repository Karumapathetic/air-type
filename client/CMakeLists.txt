cmake_minimum_required(VERSION 3.27)

project("R-Type client")

# Set C++ standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(../entityComponentSystem/include/)
include_directories(../entityComponentSystem/include/Components)
include_directories(../entityComponentSystem/include/Entities)
include_directories(../entityComponentSystem/include/Systems)

include(../cmake/CPM.cmake)

# Add raylib package
CPMAddPackage("gh:raysan5/raylib#4.5.0")

add_executable(
    rtype_client
    Main.cpp
    src/Engine.cpp
)

target_link_libraries(rtype_client raylib)
