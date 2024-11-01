/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collision.cpp
*/

#include "Collision.hpp"

namespace ECS {
    void Collision::update( Coordinator& _coordinator, Entity entity)
    {
        //this->detectCollision(_coordinator);
    }

    void Collision::detectCollision(ECS::Coordinator &gCoordinator) {
        auto entities = gCoordinator.getEntities();

        for (size_t i = 0; i < entities.size(); ++i) {
            auto entity = entities[i];
            std::string entityName = gCoordinator.getEntityName(entity);
            if (entityName == "settings") continue;

            for (size_t j = i + 1; j < entities.size(); ++j) {
                auto otherEntity = entities[j];
                std::string otherEntityName = gCoordinator.getEntityName(otherEntity);
                if (otherEntityName == "settings") continue;

                auto entitySpacial = gCoordinator.getComponent<Spacial>(entity);
                auto otherEntitySpacial = gCoordinator.getComponent<Spacial>(otherEntity);

                if (entitySpacial.position.x < otherEntitySpacial.position.x + otherEntitySpacial.size.x &&
                    entitySpacial.position.x + entitySpacial.size.x > otherEntitySpacial.position.x &&
                    entitySpacial.position.y < otherEntitySpacial.position.y + otherEntitySpacial.size.y &&
                    entitySpacial.position.y + entitySpacial.size.y > otherEntitySpacial.position.y) {
                    handleCollision(gCoordinator, entity, otherEntity);
                }
            }
        }
    }

    void Collision::handleCollision(ECS::Coordinator &gCoordinator, Entity entity, Entity otherEntity) {
        auto entityType = gCoordinator.getComponent<EntityTypes>(entity);
        if (gCoordinator.getEntityName(entity) == "player") {
            auto otherEntityType = gCoordinator.getComponent<EntityTypes>(otherEntity);
            if (otherEntityType.type == "enemy") {
                std::cout << "Player collided with an enemy" << std::endl;
            }
        } else if (entityType.type == "enemy" && gCoordinator.getEntityName(otherEntity) == "missile") {
            gCoordinator.addEvent(entity, "damage" + std::to_string(otherEntity));
            std::cout << "Missile collided with an enemy" << std::endl;
            return;
        }
    }
}
