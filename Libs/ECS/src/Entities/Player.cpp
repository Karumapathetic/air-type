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
        gCoordinator.addComponent(entity, ECS::Cooldown());
        auto &cooldown = gCoordinator.getComponent<ECS::Cooldown>(entity);
        cooldown.addCooldown("missile", 0.35f, -1.0f);
        gCoordinator.addComponent(entity, Life{10.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/PlayerShip.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"player", 1, -1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
