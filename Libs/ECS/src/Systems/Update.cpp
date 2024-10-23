/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** update.cpp
*/

#include "Update.hpp"

namespace ECS {
    void UpdateSystem::update( Coordinator& _coordinator){
        if (_coordinator.getFirstEvent().second == "update") {
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
            _coordinator.putEventAtEnd();
        }
    }
}