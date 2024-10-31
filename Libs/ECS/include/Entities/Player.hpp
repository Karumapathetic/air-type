/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** playerEntity
*/

#pragma once

#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief Function that handles the player entity.
     * 
     * This function handles the player entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life, and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
