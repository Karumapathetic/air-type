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
            if (_coordinator.getEntityName(entity) == "enemy") {
                // std::cout << "Enemy position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
                if (_coordinator.getComponent<Spacial>(entity).position.x < 0) {
                    _coordinator.destroyEntity(entity);
                    continue;
                }
                auto &spacial = _coordinator.getComponent<Spacial>(entity);
                auto speed = _coordinator.getComponent<Speed>(entity);
                // spacial.position.x -= speed.velocity;
                //_coordinator.setEntityUpdated(entity, true);
            } else if (_coordinator.getEntityName(entity) == "missile") {
                // std::cout << "Missile position: " << _coordinator.getComponent<Spacial>(entity).position.x << std::endl;
                if (_coordinator.getComponent<Spacial>(entity).position.x > MAX_X) {
                    std::cout << "Destroying missile: " << entity << std::endl;
                    _coordinator.destroyEntity(entity);
                    continue;
                }
                auto &spacial = _coordinator.getComponent<Spacial>(entity);
                auto speed = _coordinator.getComponent<Speed>(entity);
                spacial.position.x += speed.velocity;
                _coordinator.setEntityUpdated(entity, true);
            }
        }
    }
}
