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
                        if (gCoordinator.getComponent<Spacial>(entity).position.x < 0) {
                            gCoordinator.destroyEntity(entity);
                            continue;
                        }
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto speed = gCoordinator.getComponent<Speed>(entity);
                        spacial.position.x -= speed.velocity;
                    } else if (gCoordinator.getEntityName(entity) == "missile") {
                        std::cout << "Missile position: " << gCoordinator.getComponent<Spacial>(entity).position.x << std::endl;
                        if (gCoordinator.getComponent<Spacial>(entity).position.x > 2000) {
                            std::cout << "Destroying missile: " << entity << std::endl;
                            gCoordinator.destroyEntity(entity);
                            continue;
                        }
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto speed = gCoordinator.getComponent<Speed>(entity);
                        spacial.position.x += speed.velocity;
                    }
                }
            }
        protected:
        private:
    };
}
