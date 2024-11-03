/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Move.cpp
*/

#include "Move.hpp"

namespace ECS {
    void Move::update( Coordinator& _coordinator, Entity entity)
    {
        // std::cout << "Moving: " << _coordinator.getFirstEvent().second << std::endl;
        this->MoveEntities(_coordinator, entity);
    }

    bool Move::MoveEntities(Coordinator &coordinator, Entity entity) {
        auto &entityPos = coordinator.getComponent<Spacial>(entity);
        auto &entitySpeed = coordinator.getComponent<Speed>(entity);
        std::string entityName = coordinator.getEntityName(entity);
            //std::cout << "System Move : " << params << std::endl;
        if (entityName == "player") {
            if (entitySpeed.vertically == true) {
                entityPos.position.y += entitySpeed.velocity;
            } else {
                entityPos.position.x += entitySpeed.velocity;
            }
            if (entitySpeed.velocity != 0.0f)
                coordinator.setEntityUpdated(entity, true);
            entitySpeed.velocity = 0.0f;
            entitySpeed.vertically = false;
            return true;
        }
        return false;
    }
}