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

#include "EcsValues.hpp"

class EntityManager {
    public:
        EntityManager() {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                availableEntities.push(entity);
            }
        }

        Entity CreateEntity(const std::string& name) {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

            Entity id = availableEntities.front();
            availableEntities.pop();
            ++livingEntityCount;
            entityNames[id] = name;

            return id;
        }

        void DestroyEntity(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");

            signatures[entity].reset();
            entityNames.erase(entity);
            availableEntities.push(entity);
            --livingEntityCount;
        }

        void SetSignature(Entity entity, Signature signature) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            signatures[entity] = signature;
        }

        Signature GetSignature(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return signatures[entity];
        }

        void SetEntityName(Entity entity, const std::string& name) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            entityNames[entity] = name;
        }

        std::string GetEntityName(Entity entity) {
            assert(entity < MAX_ENTITIES && "Entity out of range.");
            return entityNames[entity];
        }

    private:
        std::queue<Entity> availableEntities{};
        std::array<Signature, MAX_ENTITIES> signatures{};
        std::unordered_map<Entity, std::string> entityNames{};
        uint32_t livingEntityCount{};
};
