/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Move
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"
#include "Behaviour.hpp"

namespace ECS {
    /**
     * @brief System that handles the movement of entities.
     */
    class Move : public ISystem {
        public:
            void update( Coordinator& _coordinator, Entity entity);
            /**
             * @brief Moves the entities based on the given parameters.
             * 
             * The parameters can be "up", "down", "left", or "right".
             * 
             * @param coordinator The coordinator that contains the entities.
             * @param entity The entity to move.
             * @param params The parameters to move the entity.
             * 
             * @return bool
             */
            bool MoveEntities(Coordinator &coordinator, Entity entity);
        protected:
        private:
    };
}
