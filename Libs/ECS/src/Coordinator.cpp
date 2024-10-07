/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#include "Coordinator.hpp"
#include "Draw.hpp"

namespace ECS {
    void Coordinator::init() {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();
        _entities.resize(MAX_ENTITIES);
        for (size_t i = 0; i < _entities.size(); ++i) {
            _entities[i] = Entity(); // Ou une valeur par défaut appropriée
        }

        // Initialisation des handlers
        entityHandlers = {
            {"player", playerHandler},
            {"enemy", enemyHandler},
            {"missile", missileHandler},
            {"background", backgroundHandler},
            {"settings", settingsHandler},
            {"collectible", collectibleHandler}
        };

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
        Entity id = entityManager->createEntity(name);
        this->setEntities(id, id);
        return id;
    }

    void Coordinator::destroyEntity(Entity entity) {
        entityManager->destroyEntity(entity);
        componentManager->entityDestroyed(entity);
        systemManager->entityDestroyed(entity);
        this->setEntities(entity, INVALID_ENTITY);
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

    std::vector<Entity> Coordinator::getEntities() {
        return _entities;
    }

    Entity Coordinator::getEntity(std::string name) {
        for (Entity entity : _entities) {
            if (this->getEntityName(entity) == name) {
                return entity;
            }
        }
        return INVALID_ENTITY;
    }

    void Coordinator::setEntities(std::size_t index, Entity entity) {
        if (index < _entities.size()) {
            _entities[index] = entity;
        } else {
            std::cerr << "Index out of bounds: " << index << std::endl;
        }
    }

    void Coordinator::initEntities() {
        auto entities = this->getEntities();
        for (const Entity& entity : entities) {
            std::string name = this->getEntityName(entity);
            bool initialized = this->getEntityInitialized(entity);

            if (!initialized) {
                this->createEntityFromType(name, entity);
            }
        }
    }

    void Coordinator::createEntityFromType(const std::string &type, std::uint32_t entity) {
        std::cout << "Creating entity from type: " << type << std::endl;
        auto it = entityHandlers.find(type);
        if (it != entityHandlers.end()) {
            std::cout << "Found handler for entity type: " << type << std::endl;
            it->second(*this, entity);
        }
    }

    Coordinator Coordinator::initEngine() {
        Coordinator gCoordinator;

        // Init engine and register components and systems
        gCoordinator.init();
        auto drawSystem = gCoordinator.registerCoordSystem<ECS::Draw>();

        Signature drawSignature;
        drawSignature.set(gCoordinator.getComponentType<Images>());
        gCoordinator.setSystemSignature<ECS::Draw>(drawSignature);

        // Create entities
        gCoordinator.createEntity("settings");
        gCoordinator.createEntity("player");
        gCoordinator.initEntities();

        return gCoordinator;
    }
}