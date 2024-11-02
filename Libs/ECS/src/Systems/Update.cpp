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
        if (!_coordinator.hasComponent(entity, _coordinator.getComponentType<EntityTypes>())) return;
        auto entityType = _coordinator.getComponent<EntityTypes>(entity);
        if (entityType.type == "enemy") {
            // std::cout << "Enemy position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
            auto &spacial = _coordinator.getComponent<Spacial>(entity);
            if (spacial.position.x + spacial.size.x < 0) {
                spacial.position.x = MAX_X;
                // _coordinator.destroyEntity(entity);
                return;
            }
            // auto speed = _coordinator.getComponent<Speed>(entity);
            // auto pathing = _coordinator.getComponent<Pathing>(entity);
            // pathing.pathing->updatePosition(spacial.position, speed.velocity);
            // _coordinator.setEntityUpdated(entity, true);
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
