/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#pragma once

#include <memory>

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

class Coordinator {
    public:
        void init() {
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
        }


        Entity createEntity(const std::string& name) {
            return entityManager->createEntity(name);
        }

        void destroyEntity(Entity entity) {
            entityManager->destroyEntity(entity);
            componentManager->entityDestroyed(entity);
            systemManager->entityDestroyed(entity);
        }

        std::string getEntityName(Entity entity) {
            return entityManager->getEntityName(entity);
        }

        void setEntityName(Entity entity, bool initialized) {
            entityManager->setEntityInitialized(entity, initialized);
        }

        bool getEntityInitialized(Entity entity) {
            return entityManager->getEntityInitialized(entity);
        }

        void setEntityInitialized(Entity entity, bool initialized) {
            entityManager->setEntityInitialized(entity, initialized);
        }

        Signature getEntitySignature(Entity entity) {
            return entityManager->getSignature(entity);
        }

        void setEntitySignature(Entity entity, Signature signature) {
            entityManager->setSignature(entity, signature);
        }

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

    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
};

class CoordinatorInstance {
    public:
        static Coordinator& getInstance() {
            static Coordinator instance;
            return instance;
        }
};