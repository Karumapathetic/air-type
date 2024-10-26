/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** missileEntity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void missileHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{1.0f, 1.0f}, {60.0f, 12.0f}});
        gCoordinator.addComponent(entity, Power{3.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{1.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{5.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/MissileKill.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"missile", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
