/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Collision
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the collision between entities.
     */
    class Collision : public ISystem {
        public:
            void update(Coordinator& _coordinator, Entity entity);
            /**
             * @brief Detects collisions between entities.
             * 
             * @param gCoordinator The coordinator that contains the entities.
             */
            void detectCollision(ECS::Coordinator &gCoordinator, Entity entity);

            void handleCollision(ECS::Coordinator &gCoordinator, Entity entity, Entity otherEntity);
        protected:
        private:
    };
}
