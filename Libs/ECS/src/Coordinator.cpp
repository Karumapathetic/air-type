/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS {
    void Coordinator::init() {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();
        this->registerComponent<Spacial>();
        this->registerComponent<Power>();
        this->registerComponent<Life>();
        this->registerComponent<Speed>();
        this->registerComponent<Images>();
        this->registerComponent<EntityTypes>();
        this->registerComponent<Keybind>();
        this->registerComponent<Sounds>();
    }

    Entity Coordinator::createEntity(const std::string& name) {
        return entityManager->createEntity(name);
    }

    void Coordinator::destroyEntity(Entity entity) {
        entityManager->destroyEntity(entity);
        componentManager->entityDestroyed(entity);
        systemManager->entityDestroyed(entity);
    }

    std::string Coordinator::getEntityName(Entity entity) {
        return entityManager->getEntityName(entity);
    }

    void Coordinator::setEntityName(Entity entity, bool initialized) {
        entityManager->setEntityInitialized(entity, initialized);
    }

    bool Coordinator::getEntityInitialized(Entity entity) {
        return entityManager->getEntityInitialized(entity);
    }

    void Coordinator::setEntityInitialized(Entity entity, bool initialized) {
        entityManager->setEntityInitialized(entity, initialized);
    }

    Signature Coordinator::getEntitySignature(Entity entity) {
        return entityManager->getSignature(entity);
    }

    void Coordinator::setEntitySignature(Entity entity, Signature signature) {
        entityManager->setSignature(entity, signature);
    }
}