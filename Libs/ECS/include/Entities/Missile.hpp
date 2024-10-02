/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** missileEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the missile entity.
     * 
     * This function handles the missile entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Power, Speed, Images, and EntityTypes.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void missileHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
