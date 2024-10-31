/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settingsEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the settings entity.
     * 
     * This function handles the settings entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Keybind.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
