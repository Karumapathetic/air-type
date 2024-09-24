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
        void Init() {
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
        }


        Entity CreateEntity(const std::string& name) {
            return entityManager->CreateEntity(name);
        }

        void DestroyEntity(Entity entity) {
            entityManager->DestroyEntity(entity);
            componentManager->EntityDestroyed(entity);
            systemManager->EntityDestroyed(entity);
        }

        std::string GetEntityName(Entity entity) {
            return entityManager->GetEntityName(entity);
        }

        void SetEntityName(Entity entity, const std::string& name) {
            entityManager->SetEntityName(entity, name);
        }

        Signature GetEntitySignature(Entity entity) {
            return entityManager->GetSignature(entity);
        }

        void SetEntitySignature(Entity entity, Signature signature) {
            entityManager->SetSignature(entity, signature);
        }

        template<typename T>
        void RegisterComponent() {
            componentManager->RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component) {
            componentManager->AddComponent<T>(entity, component);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        void RemoveComponent(Entity entity) {
            componentManager->RemoveComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        template<typename T>
        T& GetComponent(Entity entity) {
            return componentManager->GetComponent<T>(entity);
        }

        template<typename T>
        ComponentType GetComponentType() {
            return componentManager->GetComponentType<T>();
        }


        template<typename T>
        std::shared_ptr<T> RegisterSystem() {
            return systemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemSignature(Signature signature) {
            systemManager->SetSignature<T>(signature);
        }

    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
};

extern Coordinator gCoordinator;