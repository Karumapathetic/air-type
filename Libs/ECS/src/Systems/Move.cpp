/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Move.cpp
*/

#include "Move.hpp"

namespace ECS {
    void Move::update( Coordinator& _coordinator)
    {
        if (_coordinator.getFirstEvent().second == "up" || _coordinator.getFirstEvent().second == "down" || _coordinator.getFirstEvent().second == "left" || _coordinator.getFirstEvent().second == "right") {
            // std::cout << "Moving: " << _coordinator.getFirstEvent().second << std::endl;
            this->MoveEntities(_coordinator, _coordinator.getFirstEvent().first, _coordinator.getFirstEvent().second);
            _coordinator.removeFirstEvent();
        }
    }

    bool Move::MoveEntities(Coordinator &coordinator, Entity entity, const std::string &params) {
        auto &entityPos = coordinator.getComponent<Spacial>(entity);
        auto entitySpeed = coordinator.getComponent<Speed>(entity);
        std::string entityName = coordinator.getEntityName(entity);
        if (entityName == "player") {
            //std::cout << "System Move : " << params << std::endl;
            if (params == "up") {
                if (entityPos.position.y - entitySpeed.velocity > 0)
                    entityPos.position.y -= entitySpeed.velocity;
            } else if (params == "down") {
                if (entityPos.position.y + entitySpeed.velocity + entityPos.size.y < MAX_Y)
                    entityPos.position.y += entitySpeed.velocity;
            } else if (params == "left") {
                if (entityPos.position.x - entitySpeed.velocity > 0)
                    entityPos.position.x -= entitySpeed.velocity;
            } else if (params == "right") {
                if (entityPos.position.x + entitySpeed.velocity + entityPos.size.x < MAX_X)
                    entityPos.position.x += entitySpeed.velocity;
            }
            coordinator.setEntityUpdated(entity, true);
            return true;
        }
        return false;
    }
}