/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollectibleEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief Function that handles the collectible "force1" entity.
     * 
     * This function handles the collectible "force1" entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, and EntityTypes.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void forceOneHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the collectible "roundbit" entity.
     * 
     * This function handles the collectible "roundbit" entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, and EntityTypes and one Cooldown.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void roundbitHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the collectible "speed" entity.
     * 
     * This function handles the collectible "speed" entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, and EntityTypes.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void speedHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
