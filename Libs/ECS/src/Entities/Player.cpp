/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** playerEntity
*/

#include "Player.hpp"

namespace ECS {
    void playerHandler(Coordinator &gCoordinator, u_int32_t entity) {
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{10.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{1.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{ 0 , 1});
        gCoordinator.addComponent(entity, EntityTypes{"player", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
