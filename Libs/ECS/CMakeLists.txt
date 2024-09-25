add_library(
    ECS STATIC
    src/Coordinator.cpp
    src/Engine.cpp
    src/EntityManager.cpp
    src/SystemManager.cpp

    src/Components/ComponentArray.cpp
    src/Components/Components.cpp
    src/Components/IComponentArray.cpp

    src/Systems/Collision.cpp
    src/Systems/Damage.cpp
    src/Systems/Draw.cpp
    src/Systems/Heal.cpp
    src/Systems/Killed.cpp
    src/Systems/Move.cpp
    src/Systems/Shoot.cpp
    src/Systems/Spawn.cpp
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