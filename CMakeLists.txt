cmake_minimum_required(VERSION 3.27)
project(R-Type)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# CPM.cmake download location
# set(CPM_DOWNLOAD_LOCATION "cmake/CPM.cmake")

# Download CPM.cmake if it does not exist
# if (NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
#     message(STATUS "Downloading CPM.cmake")
#     file(DOWNLOAD 
#         https://github.com/cpm-cmake/CPM.cmake/releases/download/latest/CPM.cmake 
#         ${CPM_DOWNLOAD_LOCATION}
#         EXPECTED_HASH SHA256=cc155ce02e7945e7b8967ddfaff0b050e958a723ef7aad3766d368940cb15494
#         SHOW_PROGRESS
#         STATUS download_status
#     )
#     list(GET download_status 0 download_status_code)
#     if (NOT download_status_code EQUAL 0)
#         message(FATAL_ERROR "Error downloading CPM.cmake: ${download_status}")
#     endif()
# endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBRARIES ON)

add_subdirectory(Server)
add_subdirectory(Client)

add_subdirectory(Libs/ECS)
add_subdirectory(Libs/Network)
add_subdirectory(Libs/Graphics)

add_subdirectory(3rdParties/raylib)
