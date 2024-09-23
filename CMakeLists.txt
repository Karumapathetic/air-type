cmake_minimum_required(VERSION 3.27)
project(R-Type)

set(TARGET_TYPE "client" CACHE STRING "Select target to build: client or server")

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

if (TARGET_TYPE STREQUAL "client")
    message(STATUS "Building the client...")
    add_subdirectory(client)
elseif (TARGET_TYPE STREQUAL "server")
    message(STATUS "Building the server...")
    add_subdirectory(server)
else()
    message(STATUS "Invalid TARGET_TYPE. Must be 'client' or 'server'")
endif()
