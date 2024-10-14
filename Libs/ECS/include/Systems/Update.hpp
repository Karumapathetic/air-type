/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Update
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the update of entities.
     */
    class Update : public ISystem {
        public:
            void UpdatePositions(Coordinator &gCoordinator) {
                for (auto entity: gCoordinator.getEntities()) {
                    if (gCoordinator.getEntityName(entity) == "enemy") {
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto &speed = gCoordinator.getComponent<Speed>(entity);
                        spacial.position.x -= speed.velocity;
                    } else if (gCoordinator.getEntityName(entity) == "missile") {
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto &speed = gCoordinator.getComponent<Speed>(entity);
                        spacial.position.x += speed.velocity;
                    }
                }
            }
        protected:
        private:
    };
}
