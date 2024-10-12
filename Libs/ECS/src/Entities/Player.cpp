/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** playerEntity
*/

#include "Coordinator.hpp"

namespace ECS {
    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{100.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{10.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{1.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"../../../Graphics/assets/texture/PlayerShip.gif", {0.0f, 0.0f, 32.0f, 16.0f}, 1});
        gCoordinator.addComponent(entity, EntityTypes{"player", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
