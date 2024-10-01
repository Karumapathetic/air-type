/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#pragma once

#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

namespace ECS {
    class Coordinator {
        public:
            template<typename T>
            void registerComponent() {
                componentManager->registerComponent<T>();
            }

            template<typename T>
            void addComponent(Entity entity, T component) {
                componentManager->addComponent<T>(entity, component);

                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponentType<T>(), true);
                entityManager->setSignature(entity, signature);

                systemManager->entitySignatureChanged(entity, signature);
            }

            template<typename T>
            void removeComponent(Entity entity) {
                componentManager->removeComponent<T>(entity);

                auto signature = entityManager->getSignature(entity);
                signature.set(componentManager->getComponentType<T>(), false);
                entityManager->setSignature(entity, signature);

                systemManager->entitySignatureChanged(entity, signature);
            }

            template<typename T>
            T& getComponent(Entity entity) {
                return componentManager->getComponent<T>(entity);
            }

            template<typename T>
            ComponentType getComponentType() {
                return componentManager->getComponentType<T>();
            }

            template<typename T>
            std::shared_ptr<T> registerSystem() {
                return systemManager->registerSystem<T>();
            }

            template<typename T>
            void setSystemSignature(Signature signature) {
                systemManager->setSignature<T>(signature);
            }

            static Coordinator initEngine();
            void init();
            void initEntities();
            Entity createEntity(const std::string& name);
            void destroyEntity(Entity entity);
            std::string getEntityName(Entity entity);
            void setEntityName(Entity entity, bool initialized);
            bool getEntityInitialized(Entity entity);
            void setEntityInitialized(Entity entity, bool initialized);
            Signature getEntitySignature(Entity entity);
            void setEntitySignature(Entity entity, Signature signature);
            std::vector<Entity> getEntities();

        private:
            std::unique_ptr<ComponentManager> componentManager;
            std::unique_ptr<EntityManager> entityManager;
            std::unique_ptr<SystemManager> systemManager;
            std::unordered_map<std::string, std::function<void(Coordinator&, std::uint32_t)>> entityHandlers;
            std::vector<Entity> _entities;
            void createEntityFromType(const std::string &type, std::uint32_t entity);
    };

    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity);
    void enemyHandler(Coordinator &gCoordinator, std::uint32_t entity);
    void missileHandler(Coordinator &gCoordinator, std::uint32_t entity);
    void backgroundHandler(Coordinator &gCoordinator, std::uint32_t entity);
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity);
    void collectibleHandler(Coordinator &gCoordinator, std::uint32_t entity);
}