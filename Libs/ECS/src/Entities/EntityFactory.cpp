/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client engine
*/

#include "EntityFactory.hpp"

namespace ECS {
    void EntityFactory::createEntity(Coordinator &gCoordinator, const std::string &type, std::uint32_t entity) {
        auto it = entityHandlers.find(type);
        if (it != entityHandlers.end()) {
            it->second(gCoordinator, entity);
        }
    }

    EntityFactory::EntityFactory() {
        entityHandlers = {
            {"player", playerHandler},
            {"enemy", enemyHandler},
            {"missile", missileHandler},
            {"background", backgroundHandler},
            {"settings", settingsHandler},
            {"collectible", collectibleHandler}
        };
    }

    Coordinator mainEngine() {
        Coordinator gCoordinator;
        EntityFactory entityFactory;

        // Init engine and register components and systems
        gCoordinator.init();
        std::vector<Entity> entities(MAX_ENTITIES);

        // Create entities
        entities[0] = gCoordinator.createEntity("player");

        for (const Entity& entity : entities) {
            std::string name = gCoordinator.getEntityName(entity);
            bool initialized = gCoordinator.getEntityInitialized(entity);

            // Depending on the entity type, initialize the entity
            if (!initialized) {
                entityFactory.createEntity(gCoordinator, name, entity);
            }
        }
        return gCoordinator;
    }
}