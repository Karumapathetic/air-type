/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** EntityManager
*/

#include "EntityManager.hpp"

namespace ECS {
    EntityManager::EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            availableEntities.push(entity);
        }
    }

    Entity EntityManager::createEntity(const std::string& name)
    {
        assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;
        entityNames[id] = name;
        entityInitialized[id] = false;

        return id;
    }

    void EntityManager::destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        signatures[entity].reset();
        entityNames.erase(entity);
        entityInitialized.erase(entity);
        availableEntities.push(entity);
        --livingEntityCount;
    }

    void EntityManager::setSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        signatures[entity] = signature;
    }

    Signature EntityManager::getSignature(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return signatures[entity];
    }

    void EntityManager::setEntityName(Entity entity, const std::string& name)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        entityNames[entity] = name;
    }

    std::string EntityManager::getEntityName(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return entityNames[entity];
    }

    void EntityManager::setEntityInitialized(Entity entity, const bool initialized)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        entityInitialized[entity] = initialized;
    }

    bool EntityManager::getEntityInitialized(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return entityInitialized[entity];
    }
}
