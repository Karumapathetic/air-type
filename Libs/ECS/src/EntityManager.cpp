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

        _entities.resize(MAX_ENTITIES);
        for (size_t i = 0; i < _entities.size(); ++i) {
            _entities[i] = Entity();
        }
    }

    Entity EntityManager::createEntity(const std::string& name)
    {
        // std::cout << livingEntityCount << " entities created" << std::endl;
        assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = availableEntities.front();
        availableEntities.pop();
        livingEntityCount++;
        entityNames[id] = name;
        entityInitialized[id] = false;
        entityUpdated[id] = true;
        setEntities(id, id);

        return id;
    }

    void EntityManager::destroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        this->setEntities(entity, INVALID_ENTITY);
        entityUpdated.erase(entity);
        entityInitialized.erase(entity);
        entityNames.erase(entity);
        signatures[entity].reset();
        if (livingEntityCount != 0)
            livingEntityCount--;
        availableEntities.push(entity);
    }

    bool EntityManager::isEntityValid(Entity entity) const {
        return entity != INVALID_ENTITY;
    }

    std::vector<Entity> EntityManager::getEntities()
    {
        std::vector<Entity> validEntities;
        for (const Entity& entity : _entities) {
            if (isEntityValid(entity)) {
                validEntities.push_back(entity);
            }
        }
        return validEntities;
    }

    void EntityManager::setEntities(std::size_t index, Entity entity)
    {
        if (index < _entities.size()) {
            _entities[index] = entity;
        } else {
            std::cerr << "Index out of bounds: " << index << std::endl;
        }
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

    void EntityManager::setEntityUpdated(Entity entity, const bool updated)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        entityUpdated[entity] = updated;
    }

    bool EntityManager::getEntityUpdated(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range.");
        return entityUpdated[entity];
    }
}
