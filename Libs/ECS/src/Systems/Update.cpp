/*
** EPITECH PROJECT, 2024
** Air-type
** File description:
** Update.Cpp
*/

#include "Update.hpp"

namespace ECS {
    void Update::update( Coordinator& _coordinator)
    {
        this->gameUpdate(_coordinator);
        if (_coordinator.getFirstEvent().second == "update") {
            _coordinator.removeFirstEvent();
        }
    }

    void Update::gameUpdate(Coordinator& _coordinator)
    {
        for (auto entity: _coordinator.getEntities()) {
            if (!_coordinator.hasComponent(entity, _coordinator.getComponentType<EntityTypes>())) continue;
            auto entityType = _coordinator.getComponent<EntityTypes>(entity);
            if (entityType.type == "enemy") {
                // std::cout << "Enemy position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
                auto &spacial = _coordinator.getComponent<Spacial>(entity);
                if (spacial.position.x + spacial.size.x < 0) {
                    spacial.position.x = MAX_X;
                    // _coordinator.destroyEntity(entity);
                    continue;
                }
                // auto speed = _coordinator.getComponent<Speed>(entity);
                // auto pathing = _coordinator.getComponent<Pathing>(entity);
                // pathing.pathing->updatePosition(spacial.position, speed.velocity);
                // _coordinator.setEntityUpdated(entity, true);
            } else if (entityType.type == "missile") {
                // std::cout << "Missile position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
                auto &spacial = _coordinator.getComponent<Spacial>(entity);
                if (spacial.position.x - spacial.size.x > MAX_X) {
                    std::cout << "Destroying missile: " << entity << std::endl;
                    _coordinator.destroyEntity(entity);
                    continue;
                }
                auto speed = _coordinator.getComponent<Speed>(entity);
                spacial.position.x += speed.velocity;
                _coordinator.setEntityUpdated(entity, true);
            }
        }
    }
}
