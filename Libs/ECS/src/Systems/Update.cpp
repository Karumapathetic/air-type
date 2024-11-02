/*
** EPITECH PROJECT, 2024
** Air-type
** File description:
** Update.Cpp
*/

#include "Update.hpp"

namespace ECS {
    void Update::update( Coordinator& _coordinator, Entity entity)
    {
        this->gameUpdate(_coordinator, entity);
    }

    void Update::gameUpdate(Coordinator& _coordinator, Entity entity)
    {
        if (_coordinator.getEntityName(entity) == "enemy") {
            // std::cout << "Enemy position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
            if (_coordinator.getComponent<Spacial>(entity).position.x < 0) {
                std::cout << "Destroying enemy: " << entity << std::endl;
                _coordinator.addEvent(entity, "destroy");
                return;
            }
            auto &spacial = _coordinator.getComponent<Spacial>(entity);
            auto speed = _coordinator.getComponent<Speed>(entity);
            // spacial.position.x -= speed.velocity;
            //_coordinator.setEntityUpdated(entity, true);
        } else if (_coordinator.getEntityName(entity) == "missile") {
            // std::cout << "Missile position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
            if (_coordinator.getComponent<Spacial>(entity).position.x > MAX_X) {
                std::cout << "Destroying missile: " << entity << std::endl;
                _coordinator.addEvent(entity, "destroy");
                return;
            }
            auto &entityCooldown = _coordinator.getComponent<Cooldown>(entity);
            if (entityCooldown.getRemainingCooldown("missile") <= 0.0f) {
                auto &spacial = _coordinator.getComponent<Spacial>(entity);
                auto speed = _coordinator.getComponent<Speed>(entity);
                spacial.position.x += speed.acceleration;
                _coordinator.setEntityUpdated(entity, true);
                entityCooldown.activation["missile"].second = std::chrono::steady_clock::now();
            }
        }
    }
}
