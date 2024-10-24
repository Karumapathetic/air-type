/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shoot.cpp
*/

#include "Shoot.hpp"

namespace ECS {
    void Shoot::update( Coordinator& _coordinator)
    {
        if (_coordinator.getFirstEvent().second == "shoot") {
            this->MissileShoot(_coordinator, _coordinator.getFirstEvent().first);
        }
    }

    bool Shoot::MissileShoot(Coordinator &coordinator, Entity entity) {
        auto &entityCooldown = coordinator.getComponent<Cooldown>(entity);
        if (entityCooldown.getRemainingCooldown("missile") > 0.0f) {
            coordinator.removeFirstEvent();
            return false;
        }
        entityCooldown.activation["missile"].second = std::chrono::steady_clock::now();
        auto entityPos = coordinator.getComponent<Spacial>(entity);
        Entity missile = coordinator.createEntity("missile");
        coordinator.initEntities();
        auto &missilePos = coordinator.getComponent<Spacial>(missile);
        missilePos.position.x = entityPos.position.x;
        missilePos.position.y = entityPos.position.y;
        std::cout << "Shooting missile: " << missile << std::endl;
            coordinator.removeFirstEvent();
        return true;
    }
}

