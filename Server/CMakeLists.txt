add_executable(r-type_server
    Main.cpp
)

target_link_directories(
    r-type_server PUBLIC
    "../Libs/ECS"
    "../Libs/Network"
)

target_link_libraries(
    r-type_server PUBLIC
    ECS
    Network
)

target_include_directories(
    r-type_server PUBLIC
    "include"
    "../Libs/ECS/include"
    "../Libs/ECS/include/Components"
    "../Libs/ECS/include/Entities"
    "../Libs/ECS/include/Systems"
    "../Libs/Network/include"
)
