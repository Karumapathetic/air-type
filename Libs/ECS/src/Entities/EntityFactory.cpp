/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client engine
*/

#include "EntityFactory.hpp"

namespace ECS {
    void EntityFactory::createEntity(Coordinator &gCoordinator, const std::string &type, u_int32_t entity) {
        auto it = entityHandlers.find(type);
        if (it != entityHandlers.end()) {
            it->second(gCoordinator, entity);
        }
    }

    EntityFactory::EntityFactory() {
        entityHandlers = {
            {"player", playerHandler},
            {"ennemy", ennemyHandler},
            {"missile", missileHandler},
            {"background", backgroundHandler},
            {"settings", settingsHandler},
            {"collectible", collectibleHandler}
        };
    }

    int mainEngine() {
        Coordinator gCoordinator;
        EntityFactory entityFactory;

        // Init engine and register components and systems
        gCoordinator.init();
        std::vector<Entity> entities(MAX_ENTITIES);

        // Create entities
        entities[0] = gCoordinator.createEntity("background");
        entities[1] = gCoordinator.createEntity("settings");
        entities[2] = gCoordinator.createEntity("player");
        entities[3] = gCoordinator.createEntity("missile");
        for (int x = 4; x < 10; ++x) {
            entities[x] = gCoordinator.createEntity("ennemy");
        }
        for (int x = 11; x < 15; ++x) {
            entities[x] = gCoordinator.createEntity("collectible");
        }

        for (const Entity& entity : entities) {
            std::string name = gCoordinator.getEntityName(entity);
            bool initialized = gCoordinator.getEntityInitialized(entity);

            // Depending on the entity type, initialize the entity
            if (!initialized) {
                entityFactory.createEntity(gCoordinator, name, entity);
            }
        }
        return 0;
    }
}