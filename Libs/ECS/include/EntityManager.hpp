/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** EntityManager
*/

#pragma once

#include <unordered_map>
#include <string>
#include <queue>
#include <array>
#include <cassert>

#include "ECSValues.hpp"

class EntityManager {
    public:
        EntityManager() {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                availableEntities.push(entity);
            }
        }

        Entity createEntity(const std::string& name) {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

            Entity id = availableEntities.front();
            availableEntities.pop();
            ++livingEntityCount;
            entityNames[id] = name;
            entityInitialized[id] = false;

            return id;
        }

        void destroyEntity(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity].reset();
            entityNames.erase(entity);
            entityInitialized.erase(entity);
            availableEntities.push(entity);
            --livingEntityCount;
        }

        void setSignature(Entity entity, Signature signature) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            signatures[entity] = signature;
        }

        Signature getSignature(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return signatures[entity];
        }

        void setEntityName(Entity entity, const std::string& name) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            entityNames[entity] = name;
        }

        std::string getEntityName(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return entityNames[entity];
        }

        void setEntityInitialized(Entity entity, const bool initialized) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            entityInitialized[entity] = initialized;
        }

        bool getEntityInitialized(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return entityInitialized[entity];
        }

    private:
        std::queue<Entity> availableEntities{};
        std::array<Signature, MAX_ENTITIES> signatures{};
        std::unordered_map<Entity, std::string> entityNames{};
        std::unordered_map<Entity, bool> entityInitialized{};
        uint32_t livingEntityCount{};
};
