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
            std::shared_ptr<T> registerSystem()
            {
                std::string typeName = typeid(T).name();
                assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

                auto system = std::make_shared<T>();
                systems.insert({typeName, system});
                return system;
            }

            template<typename T>
            std::shared_ptr<T> getSystem()
            {
                std::string typeName = typeid(T).name();
                auto system = std::make_shared<T>();
                return system;
            }

            Signature getSystemSignature(const std::string& typeName)
            {
                return signatures.at(typeName);
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
            void setSignature(Signature signature)
            {
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
            void entityDestroyed(Entity entity);

            /**
             * @brief Handles the change of an entity signature.
             * 
             * This function is called when the signature of an entity changes. It updates the entity in all systems.
             * 
             * @param entity The entity whose signature has changed.
             * @param entitySignature The new signature of the entity.
             */
            void entitySignatureChanged(Entity entity, Signature entitySignature);

            /**
             * @brief Returns a constant reference to the map of systems.
             * 
             * This function allows access to the systems managed by the SystemManager.
             * The map is keyed by the type of the system (obtained using typeid(T).name())
             * and the value is a shared pointer to the system.
             * 
             * @return A constant reference to the map of systems.
             */
            const std::unordered_map<std::string, std::shared_ptr<ISystem>>& getSystems() const
            {
                return systems;
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
