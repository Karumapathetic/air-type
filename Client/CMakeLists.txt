add_executable(r-type_client
    Main.cpp
)

include(../CPM/CPM.cmake)

# Add raylib package
CPMAddPackage("gh:raysan5/raylib#4.5.0")

target_link_directories(
    r-type_client PUBLIC
    "../Libs/ECS"
    "../Libs/Network"
    "../Libs/Graphics"
)

target_link_libraries(
    r-type_client PUBLIC
    ECS
    Network
    Graphics
    raylib
)

target_include_directories(
    r-type_client PUBLIC
    "include"
    "../Libs/ECS/include"
    "../Libs/ECS/include/Components"
    "../Libs/ECS/include/Entities"
    "../Libs/ECS/include/Systems"
    "../Libs/Network/include"
    "../Libs/Graphics/include"
)
