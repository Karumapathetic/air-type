/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollectibleEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the collectible entity.
     * 
     * This function handles the collectible entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, and EntityTypes.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void collectibleHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
