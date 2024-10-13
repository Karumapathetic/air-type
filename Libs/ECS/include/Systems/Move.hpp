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
            Move() {}
            ~Move() {}

            void MoveEntities(Coordinator &coordinator, Entity entity, const std::string &params = "nothing") {
                auto &entityPos = coordinator.getComponent<Spacial>(entity);
                std::string entityName = coordinator.getEntityName(entity);
                if (entityName == "player") {
                    switch (params) {
                        case "up":
                            entityPos.position.y--;
                            break;
                        case "down":
                            entityPos.position.y++;
                            break;
                        case "left":
                            entityPos.position.x--;
                            break;
                        case "right":
                            entityPos.position.x++;
                            break;
                        default:
                            break;
                    }
                } else if (entityName == "enemy") {
                    entityPos.position.x--;
                } else if (entityName == "missile") {
                    entityPos.position.x++;
                } else {
                    continue;
                }
            }
        protected:
        private:
    };
}
