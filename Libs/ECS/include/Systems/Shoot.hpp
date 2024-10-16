/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Shoot
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the shooting of entities.
     */
    class Shoot : public ISystem {
        public:
            void MissileShoot(Coordinator &coordinator, Entity entity) {
                auto &entityCooldown = coordinator.getComponent<Cooldown>(entity);
                if (entityCooldown.getRemainingCooldown("missile") > 0.0f)
                    return;
                entityCooldown.activation["missile"].second = std::chrono::steady_clock::now();
                std::cout << "SHOOT" << std::endl;
                auto entityPos = coordinator.getComponent<Spacial>(entity);
                Entity missile = coordinator.createEntity("missile");
                coordinator.initEntities();
                auto &missilePos = coordinator.getComponent<Spacial>(missile);
                missilePos.position.x = entityPos.position.x;
                missilePos.position.y = entityPos.position.y;
                std::cout << "Shooting missile: " << missile << std::endl;
            }
        protected:
        private:
    };
}
