/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollectibleEntity.cpp
*/

#include "Collectible.hpp"

namespace ECS {
    void forceOneHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}});
        gCoordinator.addComponent(entity, Speed{0.0f, 0.0f, false});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/force1.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"collectible", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void roundbitHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}});
        gCoordinator.addComponent(entity, Speed{0.0f, 0.0f, false});
        gCoordinator.addComponent(entity, ECS::Cooldown());
        auto &cooldown = gCoordinator.getComponent<ECS::Cooldown>(entity);
        cooldown.addCooldown("missile", 1.0f, -1.0f);
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/roundbit.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"collectible", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void speedHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}});
        gCoordinator.addComponent(entity, Speed{0.0f, 1.0f, false});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/speed.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"collectible", 2});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
