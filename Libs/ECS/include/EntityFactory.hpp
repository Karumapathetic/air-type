/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Engine.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Coordinator.hpp"
#include "Components.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Background.hpp"
#include "Settings.hpp"
#include "Collectible.hpp"

namespace ECS {
    /**
     * @brief Class that will handle the creation of entities.
     * 
     * This class is used to handle the creation of entities. It provides functions to create entities
     * of different types.
     * 
     */
    class EntityFactory {
        public:
            /**
             * @brief Constructor of the EntityFactory.
             */
            EntityFactory();

            /**
             * @brief Function that will create an entity.
             * 
             * This function will create an entity of a given type.
             * 
             * @param gCoordinator The coordinator of the game.
             * @param type The type of the entity.
             * @param entity The entity to be created.
             */
            void createEntity(Coordinator &gCoordinator, const std::string &type, std::uint32_t entity);

        private:
            /**
             * @brief Variable that will store the entity handlers.
             */
            std::unordered_map<std::string, std::function<void(Coordinator&, std::uint32_t)>> entityHandlers;
    };

    /**
     * @brief Function that will create the main engine of the game.
     * 
     * This function initializes the coordinator and creates all the entities.
     * 
     * @return The coordinator of the game.
     */
    Coordinator mainEngine();
}
