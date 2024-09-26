/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** SystemManager
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <cassert>
#include <iostream>

#include "ISystem.hpp"

namespace ECS {
    class SystemManager {
        public:
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                std::string typeName = typeid(T).name();
                assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

                auto system = std::make_shared<T>();
                systems.insert({typeName, system});
                return system;
            }

            template<typename T>
            void setSignature(Signature signature) {
                std::string typeName = typeid(T).name();
                assert(systems.find(typeName) != systems.end() && "System used before registered.");

                signatures.insert({typeName, signature});
            }

            void entityDestroyed(Entity entity)
            {
                for (auto const& pair : systems) {
                    auto const& system = pair.second;
                    system->entities.erase(entity);
                }
            }

            void entitySignatureChanged(Entity entity, Signature entitySignature)
            {
                for (auto const& pair : systems) {
                    auto const& type = pair.first;
                    auto const& system = pair.second;
                    auto const& systemSignature = signatures[type];

                    if ((entitySignature & systemSignature) == systemSignature) {
                        system->entities.insert(entity);
                    } else {
                        system->entities.erase(entity);
                    }
                }
            }

        private:
            std::unordered_map<std::string, Signature> signatures{};
            std::unordered_map<std::string, std::shared_ptr<ISystem>> systems{};
    };
}