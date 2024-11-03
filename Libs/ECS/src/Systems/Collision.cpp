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
        const auto &entities = gCoordinator.getEntities();

        for (const auto &otherEntity : entities) {
            std::string otherEntityName = gCoordinator.getEntityName(otherEntity);
            if (otherEntityName == "settings" || entity == otherEntity ||
                !gCoordinator.hasComponent(entity, gCoordinator.getComponentType<Spacial>()) ||
                !gCoordinator.hasComponent(otherEntity, gCoordinator.getComponentType<Spacial>())) continue;

            auto &entitySpacial = gCoordinator.getComponent<Spacial>(entity);
            auto &otherEntitySpacial = gCoordinator.getComponent<Spacial>(otherEntity);
            if (entitySpacial.position.x < otherEntitySpacial.position.x + otherEntitySpacial.size.x &&
                entitySpacial.position.x + entitySpacial.size.x > otherEntitySpacial.position.x &&
                entitySpacial.position.y < otherEntitySpacial.position.y + otherEntitySpacial.size.y &&
                entitySpacial.position.y + entitySpacial.size.y > otherEntitySpacial.position.y) {
                handleCollision(gCoordinator, entity, otherEntity);
            }
        }
    }

    void Collision::handleCollision(ECS::Coordinator &gCoordinator, Entity entity, Entity otherEntity) {
        auto entityName = gCoordinator.getEntityName(entity);
        auto otherName = gCoordinator.getEntityName(otherEntity);
        auto entityType = gCoordinator.getComponent<EntityTypes>(entity);
        auto otherType = gCoordinator.getComponent<EntityTypes>(otherEntity);
        if ((entityType.type == otherType.type) ||
            (entityName == "player" && otherName == "missile") ||
            (entityName == "missile" && otherName == "player")) return;
        auto &entityLife = gCoordinator.getComponent<Life>(entity);
        auto &otherEntityPower = gCoordinator.getComponent<Power>(otherEntity);
        entityLife.damageTaken = otherEntityPower.damage;
        // std::cout << "Entity:" << otherEntity << " collided with an entity: " << entity << std::endl;
    }
}
