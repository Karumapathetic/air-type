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
        this->detectCollision(_coordinator, entity);
    }

    void Collision::detectCollision(ECS::Coordinator &gCoordinator, Entity entity) {
        std::string entityName = gCoordinator.getEntityName(entity);
        if (entityName == "settings") return;
        auto entities = gCoordinator.getEntities();

        for (size_t j = 0; j < entities.size(); ++j) {
            auto otherEntity = entities[j];
            std::string otherEntityName = gCoordinator.getEntityName(otherEntity);
            if (otherEntityName == "settings" || entity == otherEntity) continue;

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

    void Collision::handleCollision(ECS::Coordinator &gCoordinator, Entity entity, Entity otherEntity) {
        auto &entityLife = gCoordinator.getComponent<Life>(entity);
        auto &otherEntityPower = gCoordinator.getComponent<Power>(otherEntity);
        entityLife.damageTaken = otherEntityPower.damage;
        std::cout << "Entity:" << otherEntity << " collided with an entity: " << entity << std::endl;
    }
}
