/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** backgroundEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the background entity.
     * 
     * This function handles the background entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial and Images.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void backgroundHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
