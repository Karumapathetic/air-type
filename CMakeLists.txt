cmake_minimum_required(VERSION 3.27)
project(R-Type)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_STATIC_LIBRARIES ON)

add_subdirectory(Server)
add_subdirectory(Client)

add_subdirectory(Libs/ECS)
add_subdirectory(Libs/Network)
add_subdirectory(Libs/Graphics)

