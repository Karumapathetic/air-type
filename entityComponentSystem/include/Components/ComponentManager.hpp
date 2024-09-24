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

#include "EcsValues.hpp"
#include "ComponentArray.hpp"

class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent(){
            std::string typeName = typeid(T).name();
            assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

            componentTypes.insert({typeName, nextComponentType});
            componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
            ++nextComponentType;
        }

        template<typename T>
        ComponentType GetComponentType() {
            std::string typeName = typeid(T).name();
            assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

            return componentTypes[typeName];
        }

        template<typename T>
        void AddComponent(Entity entity, T component) {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template<typename T>
        void RemoveComponent(Entity entity) {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(Entity entity) {
            return GetComponentArray<T>()->GetData(entity);
        }

        void EntityDestroyed(Entity entity) {
            for (auto const& pair : componentArrays) {
                auto const& component = pair.second;
                component->EntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<std::string, ComponentType> componentTypes{};
        std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays{};
        ComponentType nextComponentType{};

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray() {
            std::string typeName = typeid(T).name();
            assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
        }
};
