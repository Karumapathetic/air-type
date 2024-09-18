cmake_minimum_required(VERSION 3.27)

project("R-Type client")

# Set C++ standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(
    rtype_client
    Main.cpp
)
