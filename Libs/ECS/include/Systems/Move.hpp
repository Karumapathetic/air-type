/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Move
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the movement of entities.
     */
    class Move : public ISystem {
        public:
            void update() {std::cout << "Move" << std::endl;}
            /**
             * @brief Moves the entities based on the given parameters.
             * 
             * The parameters can be "up", "down", "left", or "right".
             * 
             * @param coordinator The coordinator that contains the entities.
             * @param entity The entity to move.
             * @param params The parameters to move the entity.
             */
            void MoveEntities(Coordinator &coordinator, Entity entity, const std::string &params) {
                auto &entityPos = coordinator.getComponent<Spacial>(entity);
                auto entitySpeed = coordinator.getComponent<Speed>(entity);
                std::string entityName = coordinator.getEntityName(entity);
                if (entityName == "player") {
                    if (params == "up") {
                        if (entityPos.position.y - entitySpeed.velocity > 0)
                            entityPos.position.y -= entitySpeed.velocity;
                    } else if (params == "down") {
                        if (entityPos.position.y + entitySpeed.velocity < MAX_Y)
                            entityPos.position.y += entitySpeed.velocity;
                    } else if (params == "left") {
                        if (entityPos.position.x - entitySpeed.velocity > 0)
                            entityPos.position.x -= entitySpeed.velocity;
                    } else if (params == "right") {
                        if (entityPos.position.x + entitySpeed.velocity < MAX_X)
                            entityPos.position.x += entitySpeed.velocity;
                    }
                }
            }
        protected:
        private:
    };
}
