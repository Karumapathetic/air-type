/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#include "Coordinator.hpp"
#include "Collision.hpp"
#include "Shoot.hpp"
#include "Move.hpp"

namespace ECS {
    Coordinator::Coordinator() {
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
        this->registerComponent<Cooldown>();

        this->registerSystem<ECS::Collision>();
        this->registerSystem<ECS::Shoot>();
        this->registerSystem<ECS::Move>();

        Signature collisionSignature;
        collisionSignature.set(this->getComponentType<Spacial>());
        this->setSystemSignature<ECS::Collision>(collisionSignature);

        Signature shootSignature;
        shootSignature.set(this->getComponentType<Power>());
        shootSignature.set(this->getComponentType<Cooldown>());
        shootSignature.set(this->getComponentType<Spacial>());
        this->setSystemSignature<ECS::Shoot>(shootSignature);

        Signature moveSignature;
        moveSignature.set(this->getComponentType<Spacial>());
        moveSignature.set(this->getComponentType<Speed>());
        this->setSystemSignature<ECS::Move>(moveSignature);

        this->createEntity("settings");
        Entity enemy = this->createEntity("enemy");
        this->initEntities();

        auto &spacial = this->getComponent<Spacial>(enemy);
        spacial.position = {MAX_X - 100, MAX_Y / 2};
    }

    void Coordinator::initEntities()
    {
        auto entities = this->getEntities();
        for (const Entity& entity : entities) {
            std::string name = this->getEntityName(entity);
            bool initialized = this->getEntityInitialized(entity);

            if (!initialized) {
                this->createEntityFromType(name, entity);
            }
        }
    }

    Entity Coordinator::createEntity(const std::string& name) {
        Entity id = entityManager->createEntity(name);
        this->setEntities(id, id);
        std::cout << std::endl << "Entity : " << name << " have the ID : " << id << std::endl;
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

    bool Coordinator::isEntityValid(Entity entity) const {
        return entity != INVALID_ENTITY;
    }

    std::vector<Entity> Coordinator::getEntities() const {
        std::vector<Entity> validEntities;
        for (const Entity& entity : _entities) {
            if (isEntityValid(entity)) {
                validEntities.push_back(entity);
            }
        }
        return validEntities;
    }

    Entity Coordinator::getEntity(std::string name) {
        for (Entity entity : _entities) {
            if (this->getEntityName(entity) == name) {
                return entity;
            }
        }
        return INVALID_ENTITY;
    }

    Entity Coordinator::getEntityById(int id) {
        for (Entity entity : _entities) {
            std::string entityName = this->getEntityName(entity);
            if (entityName == "player") {
                auto entityType = this->getComponent<EntityTypes>(entity);
                if (entityType.id == id) {
                    return entity;
                }
            }
        }
        return INVALID_ENTITY;
    }

    void Coordinator::setEntities(std::size_t index, Entity entity)
    {
        if (index < _entities.size()) {
            _entities[index] = entity;
        } else {
            std::cerr << "Index out of bounds: " << index << std::endl;
        }
    }

    Signature Coordinator::getSystemSignature(const std::string& typeName)
    {
        return systemManager->getSystemSignature(typeName);
    }

    const std::unordered_map<std::string, std::shared_ptr<ISystem>>& Coordinator::getSystems() const
    {
        return systemManager->getSystems();
    }

    void Coordinator::setEntityUpdated(Entity entity, const bool updated)
    {
        entityManager->setEntityUpdated(entity, updated);
    }

    bool Coordinator::getEntityUpdated(Entity entity)
    {
        return entityManager->getEntityUpdated(entity);
    }

    void Coordinator::createEntityFromType(const std::string &type, std::uint32_t entity)
    {
        std::cout << "Creating entity from type: " << type << std::endl;
        auto it = entityHandlers.find(type);
        if (it != entityHandlers.end()) {
            std::cout << "Found handler for entity type: " << type << std::endl << std::endl;
            it->second(*this, entity);
        }
    }

    void Coordinator::updateComponentVector(Coordinator& coordinator, Entity entity, const std::string& params, const std::string& key)
    {
        Vector2 value;
        size_t posIndex = params.find(key);
        if (posIndex != std::string::npos) {
            size_t endPos = params.find(';', posIndex);
            std::string newValue = params.substr(posIndex + key.length(), endPos - (posIndex + key.length()));
            sscanf(newValue.c_str(), "%f,%f", &value.x, &value.y);
            ECS::Spacial currentPos = coordinator.getComponent<Spacial>(entity);
            if (key == "pos:") {
                currentPos.position = value;
            } else {
                currentPos.size = value;
            }
        }
    }

    template <typename T, typename MemberType>
    void Coordinator::updateComponentValue(Coordinator& coordinator, Entity entity, const std::string& params, const std::string& key, MemberType T::*member)
    {
        float value;
        size_t posIndex = params.find(key);
        if (posIndex != std::string::npos) {
            size_t endPos = params.find(';', posIndex);
            std::string newValue = params.substr(posIndex + key.length(), endPos - (posIndex + key.length()));
            sscanf(newValue.c_str(), "%f", &value);

            auto& component = coordinator.getComponent<T>(entity);
            component.*member = value;
        } else {
            std::cout << "Key not found" << std::endl;
        }
    }

    void Coordinator::spawnEntity(Coordinator& coordinator, const std::string& name, const std::string& params)
    {
        Vector2 position = {0, 0}, scale = {0, 0};
        float damage = 0, health = 0, armor = 0;

        ECS::Entity newEntity = coordinator.createEntity(name);
        coordinator.initEntities();
        updateComponentVector(coordinator, newEntity, params, "pos:");
        updateComponentVector(coordinator, newEntity, params, "scale:");
        updateComponentValue<Power>(coordinator, newEntity, params, "damage:", &Power::damage);
        updateComponentValue<Life>(coordinator, newEntity, params, "health:", &Life::health);
        updateComponentValue<Life>(coordinator, newEntity, params, "armor:", &Life::armor);
    }

    bool Coordinator::hasComponent(Entity entity, ComponentType componentType)
    {
        return entityManager->getSignature(entity).test(componentType);
    }

    void Coordinator::updateGame()
    {
        for (auto entity: this->getEntities()) {
            if (this->getEntityName(entity) == "enemy") {
                // std::cout << "Enemy position: " << this->getComponent<Spacial>(entity).position.x << std::endl;
                if (this->getComponent<Spacial>(entity).position.x < 0) {
                    this->destroyEntity(entity);
                    continue;
                }
                auto &spacial = this->getComponent<Spacial>(entity);
                auto speed = this->getComponent<Speed>(entity);
                // spacial.position.x -= speed.velocity;
                //this->setEntityUpdated(entity, true);
            } else if (this->getEntityName(entity) == "missile") {
                // std::cout << "Missile position: " << this->getComponent<Spacial>(entity).position.x << std::endl;
                if (this->getComponent<Spacial>(entity).position.x > MAX_X) {
                    std::cout << "Destroying missile: " << entity << std::endl;
                    this->destroyEntity(entity);
                    continue;
                }
                auto &spacial = this->getComponent<Spacial>(entity);
                auto speed = this->getComponent<Speed>(entity);
                spacial.position.x += speed.velocity;
                this->setEntityUpdated(entity, true);
            }
        }
    }

    void Coordinator::updateSystems()
    {
        for (auto& [typeName, system] : this->getSystems()) {
            Signature systemSignature = this->getSystemSignature(typeName);
            for (auto currentEntity : system->entities) {
                Signature entitySignature = this->getEntitySignature(currentEntity);

                if ((entitySignature & systemSignature) == systemSignature) {
                    if (_actionQueue.empty()) {
                        return;
                    }
                    for (int x = 0; x <= _actionQueue.size(); x++) {
                        std::cout << "x : " << x << " - " << _actionQueue.front().second << std::endl;
                        if (_actionQueue.front().first == currentEntity || _actionQueue.front().second == "update") {
                            system->update(*this);
                        } else {
                            this->putEventAtEnd();
                        }
                    }
                }
            }
        }
    }

    std::deque<std::pair<Entity, std::string>> Coordinator::getActionQueue()
    {
        return _actionQueue;
    }

    void Coordinator::addEvent(Entity id, const std::string& action)
    {
        const size_t maxQueueSize = 1000;
        if (_actionQueue.size() >= maxQueueSize) {
            _actionQueue.pop_front();
        }
        this->_actionQueue.push_back({id, action});
        // std::cout << "Event added: " << action << " for entity: " << id << std::endl;
    }

    std::pair<Entity, std::string> Coordinator::getFirstEvent() const
    {
        return _actionQueue.front();
    }

    void Coordinator::removeFirstEvent()
    {
        // std::cout << "Event removed: " << _actionQueue.front().second << " for entity: " << _actionQueue.front().first << std::endl;
        _actionQueue.pop_front();
    }

    void Coordinator::putEventAtEnd()
    {
        _actionQueue.push_back(_actionQueue.front());
        _actionQueue.pop_front();
    }
}
