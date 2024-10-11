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

namespace ECS {
    /**
     * @brief Class that will handle the entities.
     * 
     * This class is used to handle the entities. It provides functions to create and destroy entities,
     * set and get entity signatures, set and get entity names, and set and get entity initialized status.
     * 
     */
    class EntityManager {
        public:
            /**
             * @brief Constructor of the EntityManager.
             */
            EntityManager();

            /**
             * @brief Creates an entity.
             * 
             * @param name The name of the entity.
             * 
             * @return The entity.
             * 
             * @throw std::runtime_error if there are too many entities in existence.
             */
            Entity createEntity(const std::string& name);

            /**
             * @brief Destroys an entity.
             * 
             * @param entity The entity to be destroyed.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            void destroyEntity(Entity entity);

            /**
             * @brief Sets the signature of an entity.
             * 
             * @param entity The entity whose signature is to be set.
             * @param signature The signature of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            void setSignature(Entity entity, Signature signature);

            /**
             * @brief Retrieves the signature of an entity.
             * 
             * @param entity The entity whose signature is to be retrieved.
             * 
             * @return The signature of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            Signature getSignature(Entity entity);
            /**
             * @brief Set the Entity Name object
             * 
             * @param entity The entity whose name is to be set.
             * @param name The name of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            void setEntityName(Entity entity, const std::string& name);

            /**
             * @brief Retrieves the name of an entity.
             * 
             * @param entity The entity whose name is to be retrieved.
             * 
             * @return The name of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            std::string getEntityName(Entity entity);

            /**
             * @brief Sets the initialized status of an entity.
             * 
             * @param entity The entity whose initialized status is to be set.
             * @param initialized The initialized status of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            void setEntityInitialized(Entity entity, const bool initialized);

            /**
             * @brief Retrieves the initialized status of an entity.
             * 
             * @param entity The entity whose initialized status is to be retrieved.
             * 
             * @return The initialized status of the entity.
             * 
             * @throw std::runtime_error if the entity is out of range.
             */
            bool getEntityInitialized(Entity entity);

        private:
            /**
             * @brief Queue of available entities.
             */
            std::queue<Entity> availableEntities{};

            /**
             * @brief Array of entity signatures.
             * 
             * The index is the entity and the value is the signature of the entity.
             */
            std::array<Signature, MAX_ENTITIES> signatures{};

            /**
             * @brief Map of entity names.
             * 
             * The key is the entity and the value is the name of the entity.
             */
            std::unordered_map<Entity, std::string> entityNames{};

            /**
             * @brief Map of entity initialized status.
             * 
             * The key is the entity and the value is the initialized status of the entity.
             */
            std::unordered_map<Entity, bool> entityInitialized{};

            /**
             * @brief The number of living entities.
             */
            uint32_t livingEntityCount{};
    };
}
