/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** backgroundEntity.cpp
*/

#include "Background.hpp"

namespace ECS {
    void backgroundHandler(Coordinator &gCoordinator, u_int32_t entity) {
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Images{ 0 });
        gCoordinator.setEntityInitialized(entity, true);
    }
}