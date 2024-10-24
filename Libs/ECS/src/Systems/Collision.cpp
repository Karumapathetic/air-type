/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Collision.cpp
*/

#include "Collision.hpp"

namespace ECS {
    void Collision::update( Coordinator& _coordinator)
    {
        this->detectCollision(_coordinator);
    }

    void Collision::detectCollision(ECS::Coordinator &gCoordinator) {
        auto entities = gCoordinator.getEntities();
        for (size_t i = 0; i < entities.size(); ++i) {
            auto entity = entities[i];
            if (gCoordinator.getEntityName(entity) != "player"
                && gCoordinator.getEntityName(entity) != "enemy"
                && gCoordinator.getEntityName(entity) != "missile")
                continue;
            for (size_t j = i + 1; j < entities.size(); ++j) {
                auto otherEntity = entities[j];
                if (gCoordinator.getEntityName(otherEntity) != "player"
                    && gCoordinator.getEntityName(otherEntity) != "enemy"
                    && gCoordinator.getEntityName(otherEntity) != "missile")
                    continue;
                auto entitySpacial = gCoordinator.getComponent<Spacial>(entity);
                auto otherEntitySpacial = gCoordinator.getComponent<Spacial>(otherEntity);
                if (entitySpacial.position.x < otherEntitySpacial.position.x + otherEntitySpacial.scale.x &&
                    entitySpacial.position.x + entitySpacial.scale.x > otherEntitySpacial.position.x &&
                    entitySpacial.position.y < otherEntitySpacial.position.y + otherEntitySpacial.scale.y &&
                    entitySpacial.position.y + entitySpacial.scale.y > otherEntitySpacial.position.y) {
                    if (gCoordinator.getEntityName(entity) == "player" && gCoordinator.getEntityName(otherEntity) == "enemy") {
                        gCoordinator.destroyEntity(otherEntity);
                    } else if (gCoordinator.getEntityName(entity) == "enemy" && gCoordinator.getEntityName(otherEntity) == "player") {
                        gCoordinator.destroyEntity(entity);
                    } else if (gCoordinator.getEntityName(entity) == "missile" && gCoordinator.getEntityName(otherEntity) == "enemy") {
                        gCoordinator.destroyEntity(entity);
                        gCoordinator.destroyEntity(otherEntity);
                    } else if (gCoordinator.getEntityName(entity) == "enemy" && gCoordinator.getEntityName(otherEntity) == "missile") {
                        gCoordinator.destroyEntity(entity);
                        gCoordinator.destroyEntity(otherEntity);
                    }
                }
            }
        }
    }
}