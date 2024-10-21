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
            /**
             * @brief Updates the positions of the entities.
             * 
             * Updates the positions of the entities based on their speed.
             * Updates the positions of enemies and missiles.
             * 
             * @param gCoordinator The coordinator that contains the entities.
             */
            void UpdatePositions(Coordinator &gCoordinator, std::function<void(const std::string&)> send_data_func) {
                for (auto entity: gCoordinator.getEntities()) {
                    if (gCoordinator.getEntityName(entity) == "enemy") {
                        // std::cout << "Enemy position: " << gCoordinator.getComponent<Spacial>(entity).position.x << std::endl;
                        if (gCoordinator.getComponent<Spacial>(entity).position.x < 0) {
                            gCoordinator.destroyEntity(entity);
                            continue;
                        }
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto speed = gCoordinator.getComponent<Speed>(entity);
                        // spacial.position.x -= speed.velocity;
                        // send_data_func("21 " + gCoordinator.getEntityName(entity) + " " + std::to_string(entity) + " " + std::to_string(spacial.position.x) + " " + std::to_string(spacial.position.y));
                    } else if (gCoordinator.getEntityName(entity) == "missile") {
                        // std::cout << "Missile position: " << gCoordinator.getComponent<Spacial>(entity).position.x << std::endl;
                        if (gCoordinator.getComponent<Spacial>(entity).position.x > MAX_X) {
                            std::cout << "Destroying missile: " << entity << std::endl;
                            gCoordinator.destroyEntity(entity);
                            continue;
                        }
                        auto &spacial = gCoordinator.getComponent<Spacial>(entity);
                        auto speed = gCoordinator.getComponent<Speed>(entity);
                        spacial.position.x += speed.velocity;
                        send_data_func("21 " + gCoordinator.getEntityName(entity) + " " + std::to_string(entity) + " " + std::to_string(spacial.position.x) + " " + std::to_string(spacial.position.y));
                    }
                }
            }
        protected:
        private:
    };
}
