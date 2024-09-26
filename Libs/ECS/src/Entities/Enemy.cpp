/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Entity.cpp
*/

#include "Enemy.hpp"

namespace ECS {
    void enemyHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{4.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{ 0 , 1});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }
}