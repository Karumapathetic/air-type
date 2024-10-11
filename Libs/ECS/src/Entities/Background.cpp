/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** backgroundEntity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void backgroundHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}, {1.0f, 1.0f}});
        gCoordinator.addComponent(entity, Images{ 0 });
        gCoordinator.setEntityInitialized(entity, true);
    }
}