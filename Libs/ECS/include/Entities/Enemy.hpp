/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemyEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the enemy entity.
     * 
     * This function handles the enemy entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life, and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void enemyHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
