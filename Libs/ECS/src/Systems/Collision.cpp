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
        std::unordered_set<std::string> targetNames = {"player", "pata-pata", "missile"};
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

                if (entitySpacial.position.x < otherEntitySpacial.position.x + otherEntitySpacial.size.x &&
                    entitySpacial.position.x + entitySpacial.size.x > otherEntitySpacial.position.x &&
                    entitySpacial.position.y < otherEntitySpacial.position.y + otherEntitySpacial.size.y &&
                    entitySpacial.position.y + entitySpacial.size.y > otherEntitySpacial.position.y) {
                    if (gCoordinator.getEntityName(entity) == "player" && gCoordinator.getEntityName(otherEntity) == "pata-pata") {
                        std::cout << "Player collided with pata-pata" << std::endl;
                        return;
                    } else if (gCoordinator.getEntityName(entity) == "pata-pata" && gCoordinator.getEntityName(otherEntity) == "missile") {
                        gCoordinator.addEvent(entity, "damage" + std::to_string(otherEntity));
                        std::cout << "Missile collided with pata-pata" << std::endl;
                        return;
                    }
                }
            }
        }
    }
}
