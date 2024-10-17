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
