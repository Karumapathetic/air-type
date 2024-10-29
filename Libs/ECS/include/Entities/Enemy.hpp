/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Enemy.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Function that handles the pata-pata entity.
     * 
     * This function handles the pata-pata entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void patapataHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the win entity.
     * 
     * This function handles the win entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void winHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the bug entity.
     * 
     * This function handles the bug entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void bugHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the wick entity.
     * 
     * This function handles the wick entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void wickHandler(Coordinator &gCoordinator, std::uint32_t entity);

    /**
     * @brief Function that handles the geld entity.
     * 
     * This function handles the geld entity. It creates the components for the entity
     * and sets the entity as initialized. The components created are Spacial, Speed, Images, EntityTypes, Life and Power.
     * 
     * @param gCoordinator The coordinator object.
     * @param entity The entity to be handled.
     */
    void geldHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
