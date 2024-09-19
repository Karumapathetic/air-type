cmake_minimum_required(VERSION 3.27)

project("R-Type client")

# Set C++ standard for the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

include(FetchContent)

find_package(raylib QUIET)

if(NOT raylib_FOUND)
    message(STATUS "Raylib not found, fetching it...")
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.5.0
    )
    FetchContent_MakeAvailable(raylib)
else()
    message(STATUS "Raylib found.")
endif()

add_executable(
    rtype_client
    Main.cpp
)

target_link_libraries(rtype_client raylib)
