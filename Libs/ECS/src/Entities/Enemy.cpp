/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Entity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void enemyHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1800.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/EnemyShip.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 0, -1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
