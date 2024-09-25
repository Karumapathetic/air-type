/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** missileEntity.cpp
*/

#include "Missile.hpp"

namespace ECS {
    void missileHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{ 0 , 1});
        gCoordinator.addComponent(entity, EntityTypes{"missile", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }
}