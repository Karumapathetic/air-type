cmake_minimum_required(VERSION 3.27)
project("R-Type ECS Lib")

add_library(
    ECS STATIC
    src/Coordinator.cpp
    src/EntityManager.cpp
    src/SystemManager.cpp

    src/Components/ComponentArray.cpp
    src/Components/Components.cpp
    src/Components/IComponentArray.cpp

    src/Entities/Player.cpp
    src/Entities/Enemy.cpp
    src/Entities/Missile.cpp
    src/Entities/Background.cpp
    src/Entities/Settings.cpp
    src/Entities/Collectible.cpp

    src/Systems/Collision.cpp
    src/Systems/Damage.cpp
    src/Systems/Draw.cpp
    src/Systems/Heal.cpp
    src/Systems/Killed.cpp
    src/Systems/Move.cpp
    src/Systems/Shoot.cpp
    src/Systems/Update.cpp
)

target_include_directories(
    ECS PUBLIC
    "include"
    "include/Components"
    "include/Entities"
    "include/Systems"
)

target_link_libraries(
    ECS
    raylib
)