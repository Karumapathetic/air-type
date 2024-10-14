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
                        entityPos.position.y -= entitySpeed.velocity;
                    } else if (params == "down") {
                        entityPos.position.y += entitySpeed.velocity;
                    } else if (params == "left") {
                        entityPos.position.x -= entitySpeed.velocity;
                    } else if (params == "right") {
                        entityPos.position.x += entitySpeed.velocity;
                    }
                }
            }
        protected:
        private:
    };
}
