/*
** EPITECH PROJECT, 2024
** Air-type
** File description:
** Behaviour
*/

#include "Behaviour.hpp"

namespace ECS {
    void behaviour(Coordinator& _coordinator)
    {
        if (_coordinator.getActionQueue().empty())
            return;
        for (int i = 0; i < _coordinator.getActionQueue().size(); i++) {
            Entity currentEntity = _coordinator.getFirstEvent().first;
            std::string action = _coordinator.getFirstEvent().second;
            if (action == "up" || action == "down" || action == "right" || action == "left") {
                handleMovement(_coordinator, currentEntity, action);
                _coordinator.removeFirstEvent();
            } else if (action == "shoot") {
                createMissile(_coordinator, currentEntity);
            } else if (action == "destroy") {
                _coordinator.destroyEntity(currentEntity);
                _coordinator.removeFirstEvent();
            }
        }
    }

    void handleMovement(Coordinator& _coordinator, Entity entity, std::string action)
    {
        ECS::Speed &speed = _coordinator.getComponent<ECS::Speed>(entity);
        if (action == "up") {
            speed.vertically = true;
            speed.velocity -= speed.acceleration;
        } else if (action == "down") {
            speed.vertically = true;
            speed.velocity += speed.acceleration;
        } else if (action == "right") {
            speed.vertically = false;
            speed.velocity += speed.acceleration;
        } else if (action == "left") {
            speed.vertically = false;
            speed.velocity -= speed.acceleration;
        }
    }

    bool createMissile(Coordinator& _coordinator, Entity entity){
        auto &entityCooldown = _coordinator.getComponent<Cooldown>(entity);
        if (entityCooldown.getRemainingCooldown("missile") > 0.0f) {
            _coordinator.removeFirstEvent();
            return false;
        }
        entityCooldown.activation["missile"].second = std::chrono::steady_clock::now();
        auto entityPos = _coordinator.getComponent<Spacial>(entity);
        Entity missile = _coordinator.createEntity("missile");
        _coordinator.initEntities();
        auto &missilePos = _coordinator.getComponent<Spacial>(missile);
        missilePos.position.x = entityPos.position.x + entityPos.size.x + 10;
        missilePos.position.y = entityPos.position.y + entityPos.size.y / 2;
        _coordinator.removeFirstEvent();
        return true;
    }
}
