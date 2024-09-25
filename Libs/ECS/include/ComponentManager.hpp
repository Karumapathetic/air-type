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
    class ComponentManager {
        public:
            template<typename T>
            void registerComponent(){
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

                componentTypes.insert({typeName, nextComponentType});
                componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
                ++nextComponentType;
            }

            template<typename T>
            ComponentType getComponentType() {
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

                return componentTypes[typeName];
            }

            template<typename T>
            void addComponent(Entity entity, T component) {
                getComponentArray<T>()->insertData(entity, component);
            }

            template<typename T>
            void removeComponent(Entity entity) {
                getComponentArray<T>()->removeData(entity);
            }

            template<typename T>
            T& getComponent(Entity entity) {
                return getComponentArray<T>()->getData(entity);
            }

            void entityDestroyed(Entity entity) {
                for (auto const& pair : componentArrays) {
                    auto const& component = pair.second;
                    component->entityDestroyed(entity);
                }
            }

        private:
            std::unordered_map<std::string, ComponentType> componentTypes{};
            std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays{};
            ComponentType nextComponentType{};

            template<typename T>
            std::shared_ptr<ComponentArray<T>> getComponentArray() {
                std::string typeName = typeid(T).name();
                assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

                return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
            }
    };
}
