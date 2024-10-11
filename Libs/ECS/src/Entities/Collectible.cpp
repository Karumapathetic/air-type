/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollectibleEntity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void collectibleHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}, {1.0f, 1.0f}});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{ 0 });
        gCoordinator.addComponent(entity, EntityTypes{"collectible", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
