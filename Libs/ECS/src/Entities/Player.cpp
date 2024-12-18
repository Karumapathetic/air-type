/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** playerEntity
*/

#include "Player.hpp"

namespace ECS {
    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{100.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        gCoordinator.addComponent(entity, ECS::Cooldown());
        auto &cooldown = gCoordinator.getComponent<ECS::Cooldown>(entity);
        cooldown.addCooldown("missile", 0.2f, -1.0f);
        gCoordinator.addComponent(entity, Life{15.0f, 0.0f});
        gCoordinator.addComponent(entity, Speed{0.0f, 3.0f, false});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/PlayerShip.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"player", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
