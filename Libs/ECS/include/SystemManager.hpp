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
    /**
     * @brief Class that will handle the systems.
     * 
     * It provides functions to register systems, set system, signatures
     * and handle entity destruction and signature changes.
     * 
     */
    class SystemManager {
        public:
            /**
             * @brief Registers a system type.
             * 
             * @tparam T The type of the system.
             * 
             * @return The system.
             * 
             * @throw std::runtime_error if the system is registered more than once.
             */
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                std::string typeName = typeid(T).name();
                assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

                auto system = std::make_shared<T>();
                systems.insert({typeName, system});
                return system;
            }

            /**
             * @brief Sets the signature of a system.
             * 
             * @tparam T The type of the system.
             * @param signature The signature of the system.
             * 
             * @throw std::runtime_error if the system is used before registered.
             */
            template<typename T>
            void setSignature(Signature signature) {
                std::string typeName = typeid(T).name();
                assert(systems.find(typeName) != systems.end() && "System used before registered.");

                signatures.insert({typeName, signature});
            }

            /**
             * @brief Handles the destruction of an entity.
             * 
             * This function is called when an entity is destroyed. It removes the entity from all systems.
             * 
             * @param entity The entity to be destroyed.
             */
            void entityDestroyed(Entity entity)
            {
                for (auto const& pair : systems) {
                    auto const& system = pair.second;
                    system->entities.erase(entity);
                }
            }

            /**
             * @brief Handles the change of an entity signature.
             * 
             * This function is called when the signature of an entity changes. It updates the entity in all systems.
             * 
             * @param entity The entity whose signature has changed.
             * @param entitySignature The new signature of the entity.
             */
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
            /**
             * @brief Map of system signatures.
             * 
             * The key is the type of the system and the value is the signature of the system.
             */
            std::unordered_map<std::string, Signature> signatures{};

            /**
             * @brief Map of systems.
             * 
             * The key is the type of the system and the value is the system.
             */
            std::unordered_map<std::string, std::shared_ptr<ISystem>> systems{};
    };
}
