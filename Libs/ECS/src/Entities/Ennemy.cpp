/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Entity.cpp
*/

#include "Ennemy.hpp"

namespace ECS {
    void ennemyHandler(Coordinator &gCoordinator, u_int32_t entity) {
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{4.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{ 0 , 1});
        gCoordinator.addComponent(entity, EntityTypes{"ennemy", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
