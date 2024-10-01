/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ComponentArray
*/

#pragma once

#include "IComponentArray.hpp"

namespace ECS {
    /**
     * @brief A class that represents an array of components of a specific type.
     * 
     * This class is used to store components of a specific type. It provides functions
     * to insert, retrieve, and remove components from the array. It also maps entities
     * to the index of the component in the array.
     * 
     * The class inherits from the IComponentArray interface.
     * 
     * @tparam T The type of the component.
     * 
     * @see IComponentArray
     */
    template<typename T>
    class ComponentArray : public IComponentArray {
        public:
            /**
             * @brief Inserts a component associated with a given entity into the component array.
             *
             * This function adds a new component to the array and maps the entity to the index
             * of the component in the array. It ensures that the same entity is not associated
             * with more than one component.
             *
             * @tparam T The type of the component.
             * @param entity The entity to which the component is associated.
             * @param component The component to be inserted.
             *
             * @throws std::runtime_error if the entity already has a component associated with it.
             */
            void insertData(Entity entity, T component) {
                assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once.");

                size_t newIndex = size;
                entityToIndexMap[entity] = newIndex;
                indexToEntityMap[newIndex] = entity;
                componentArray[newIndex] = component;
                ++size;
            }

            /**
             * @brief Removes the component associated with a given entity from the component array.
             *
             * This function removes the component associated with the given entity from the array.
             * It ensures that the entity has a component associated with it before removing it.
             *
             * @param entity The entity whose component is to be removed.
             *
             * @throws std::runtime_error if the entity does not have a component associated with it.
             */
            void removeData(Entity entity) {
                assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component.");

                size_t indexOfRemovedEntity = entityToIndexMap[entity];
                size_t indexOfLastElement = size - 1;
                componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

                Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
                entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
                indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

                entityToIndexMap.erase(entity);
                indexToEntityMap.erase(indexOfLastElement);

                --size;
            }

            /**
             * @brief Retrieves the component associated with a given entity from the component array.
             *
             * This function retrieves the component associated with the given entity from the array.
             * It ensures that the entity has a component associated with it before retrieving it.
             *
             * @param entity The entity whose component is to be retrieved.
             *
             * @return The component associated with the entity.
             *
             * @throws std::runtime_error if the entity does not have a component associated with it.
             */
            T& getData(Entity entity) {
                assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component.");

                return componentArray[entityToIndexMap[entity]];
            }

            /**
             * @brief Called when an entity is destroyed.
             *
             * This function is called when an entity is destroyed. It removes the component
             * associated with the entity from the array.
             *
             * @param entity The entity that is destroyed.
             */
            void entityDestroyed(Entity entity) override {
                if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                    removeData(entity);
                }
            }

        private:
            /**
             * @brief An array of components of type T.
             * 
             * This array stores the components of type T. The components are stored contiguously
             * in memory to improve cache performance.
             */
            std::array<T, MAX_ENTITIES> componentArray;

            /**
             * @brief A map that maps entities to the index of the component in the array.
             * 
             * This map stores the mapping between entities and the index of the component in the
             * array. This mapping is used to retrieve the component associated with a given entity.
             */
            std::unordered_map<Entity, size_t> entityToIndexMap;

            /**
             * @brief A map that maps the index of the component in the array to the entity.
             * 
             * This map stores the mapping between the index of the component in the array and the
             * entity. This mapping is used to remove the component associated with a given entity.
             */
            std::unordered_map<size_t, Entity> indexToEntityMap;

            /**
             * @brief The number of components in the array.
             * 
             * This variable stores the number of components in the array. It is used to keep track
             * of the size of the array and to ensure that the same entity is not associated with
             * more than one component.
             */
            size_t size;
    };
}
