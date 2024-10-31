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
        if (_coordinator.getFirstEvent().second == "collision") {
            _coordinator.removeFirstEvent();
        }
    }

    void Collision::detectCollision(ECS::Coordinator &gCoordinator) {
        auto entities = gCoordinator.getEntities();
        std::unordered_set<std::string> targetNames = {"player", "pata-pata", "win", "bug", "wick", "geld", "missile"};
        bool done = false;

        for (size_t i = 0; i < entities.size(); ++i) {
            auto entity = entities[i];
            std::string entityName = gCoordinator.getEntityName(entity);
            if (targetNames.find(entityName) == targetNames.end()) continue;

            for (size_t j = i + 1; j < entities.size(); ++j) {
                auto otherEntity = entities[j];
                std::string otherEntityName = gCoordinator.getEntityName(otherEntity);
                if (targetNames.find(otherEntityName) == targetNames.end()) continue;

                auto entitySpacial = gCoordinator.getComponent<Spacial>(entity);
                auto otherEntitySpacial = gCoordinator.getComponent<Spacial>(otherEntity);
                auto otherEntityType = gCoordinator.getComponent<EntityTypes>(otherEntity);

                if (entitySpacial.position.x < otherEntitySpacial.position.x + otherEntitySpacial.size.x &&
                    entitySpacial.position.x + entitySpacial.size.x > otherEntitySpacial.position.x &&
                    entitySpacial.position.y < otherEntitySpacial.position.y + otherEntitySpacial.size.y &&
                    entitySpacial.position.y + entitySpacial.size.y > otherEntitySpacial.position.y) {
                    if (gCoordinator.getEntityName(entity) == "player" && otherEntityType.type == "enemy") {
                        std::cout << "Player collided with an enemy" << std::endl;
                        return;
                    } else if (otherEntityType.type == "enemy" && gCoordinator.getEntityName(otherEntity) == "missile") {
                        gCoordinator.addEvent(entity, "damage" + std::to_string(otherEntity));
                        std::cout << "Missile collided with an enemy" << std::endl;
                        return;
                    }
                }
            }
        }
    }
}
