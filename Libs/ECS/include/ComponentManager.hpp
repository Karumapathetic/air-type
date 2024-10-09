/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ComponentManager.hpp
*/

#pragma once

#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <cassert>
#include <iostream>

#include "ECSValues.hpp"
#include "Coordinator.hpp"
#include "ComponentArray.hpp"
#include "Components.hpp"

namespace ECS {
    /**
     * @brief Class that will handle the components.
     * 
     * This class is used to handle the components of the ECS. It provides functions to register,
     * add, remove, and retrieve components. It also stores the component types and component arrays.
     * 
     */
    class ComponentManager {
        public:
            /**
             * @brief Registers a component type.
             * 
             * This function registers a component type. It ensures that the component type is not
             * registered more than once.
             * 
             * @tparam T The type of the component.
             * 
             * @throws std::runtime_error if the component type is registered more than once.
             */
            template<typename T>
            void registerComponent()
            {
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

                componentTypes.insert({typeName, nextComponentType});
                componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
                ++nextComponentType;
            }

            /**
             * @brief Retrieves the component type of a given component.
             * 
             * This function retrieves the component type of a given component. It ensures that the
             * component is registered before retrieving its type.
             * 
             * @tparam T The type of the component.
             * 
             * @return The component type of the component.
             * 
             * @throws std::runtime_error if the component is not registered before use.
             */
            template<typename T>
            ComponentType getComponentType()
            {
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

                return componentTypes[typeName];
            }

            /**
             * @brief Adds a component to an entity.
             * 
             * This function adds a component to an entity. It ensures that the entity does not have
             * the component associated with it before adding it.
             * 
             * @tparam T The type of the component.
             * @param entity The entity to which the component is added.
             * @param component The component to be added.
             * 
             * @throws std::runtime_error if the entity already has the component associated with it.
             */
            template<typename T>
            void addComponent(Entity entity, T component)
            {
                getComponentArray<T>()->insertData(entity, component);
            }

            /**
             * @brief Removes a component from an entity.
             * 
             * This function removes a component from an entity. It ensures that the entity has the
             * component associated with it before removing it.
             * 
             * @tparam T The type of the component.
             * @param entity The entity from which the component is removed.
             * 
             * @throws std::runtime_error if the entity does not have the component associated with it.
             */
            template<typename T>
            void removeComponent(Entity entity)
            {
                getComponentArray<T>()->removeData(entity);
            }

            /**
             * @brief Retrieves the component associated with an entity.
             * 
             * This function retrieves the component associated with an entity. It ensures that the
             * entity has the component associated with it before retrieving it.
             * 
             * @tparam T The type of the component.
             * @param entity The entity whose component is to be retrieved.
             * 
             * @return The component associated with the entity.
             */
            template<typename T>
            T& getComponent(Entity entity) {
                return getComponentArray<T>()->getData(entity);
            }

            /**
             * @brief Function that will handle the destruction of an entity.
             * 
             * This function will handle the destruction of an entity. It will call the entityDestroyed
             * function of each component array.
             * 
             * @param entity The entity that is destroyed.
             */
            void entityDestroyed(Entity entity)
            {
                for (auto const& pair : componentArrays) {
                    auto const& component = pair.second;
                    component->entityDestroyed(entity);
                }
            }

        private:
            /**
             * @brief Variable that store the component types.
             */
            std::unordered_map<std::string, ComponentType> componentTypes{};

            /**
             * @brief Variable that store the component arrays.
             */
            std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays{};

            /**
             * @brief Variable that store the next component type.
             */
            ComponentType nextComponentType{};

            /**
             * @brief Function that will retrieve the component array of a given component type.
             * 
             * This function retrieves the component array of a given component type. It ensures that
             * the component is registered before retrieving its array.
             * 
             * @tparam T The type of the component.
             * 
             * @return The component array of the component type.
             * 
             * @throws std::runtime_error if the component is not registered before use.
             */
            template<typename T>
            std::shared_ptr<ComponentArray<T>> getComponentArray()
            {
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

                return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
            }
    };
}
