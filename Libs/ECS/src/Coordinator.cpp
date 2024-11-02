/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Coordinator
*/

#include "Coordinator.hpp"

namespace ECS {
    Coordinator::Coordinator() {
        componentManager = std::make_unique<ComponentManager>();
        entityManager = std::make_unique<EntityManager>();
        systemManager = std::make_unique<SystemManager>();

        entityHandlers = {
            {"player", playerHandler},
            {"pata-pata", patapataHandler},
            {"win", winHandler},
            {"bug", bugHandler},
            {"wick", wickHandler},
            {"geld", geldHandler},
            {"missile", missileHandler},
            {"settings", settingsHandler},
            {"force1", forceOneHandler}
        };

        this->registerComponent<Spacial>();
        this->registerComponent<Power>();
        this->registerComponent<Life>();
        this->registerComponent<Speed>();
        this->registerComponent<Images>();
        this->registerComponent<EntityTypes>();
        this->registerComponent<Keybind>();
        this->registerComponent<Cooldown>();
        this->registerComponent<Pathing>();

        this->registerSystem<ECS::Move>();
        this->registerSystem<ECS::Damage>();
        this->registerSystem<ECS::Collision>();
        this->registerSystem<ECS::Update>();

        Signature moveSignature;
        moveSignature.set(this->getComponentType<Spacial>());
        moveSignature.set(this->getComponentType<Speed>());
        this->setSystemSignature<ECS::Move>(moveSignature);

        Signature damageSignature;
        damageSignature.set(this->getComponentType<Life>());
        damageSignature.set(this->getComponentType<Power>());
        this->setSystemSignature<ECS::Damage>(damageSignature);

        Signature collisionSignature;
        collisionSignature.set(this->getComponentType<Spacial>());
        this->setSystemSignature<ECS::Collision>(collisionSignature);

        Signature updateSignature;
        updateSignature.set(this->getComponentType<Spacial>());
        updateSignature.set(this->getComponentType<Speed>());
        this->setSystemSignature<ECS::Update>(updateSignature);

        this->createEntity("settings");
        Entity enemy = this->createEntity("pata-pata");
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
        this->initEntities();
        std::cout << "Entity : " << name << " have the ID : " << id << std::endl << std::endl;
        return id;
    }

    void Coordinator::destroyEntity(Entity entity) {
        std::string entityName = getEntityName(entity);
        pushKilledQueue(std::pair(entity, entityName));
        std::cout << "Destroying : " << entity << std::endl;
        entityManager->destroyEntity(entity);
        componentManager->entityDestroyed(entity);
        systemManager->entityDestroyed(entity);
    }

    std::string Coordinator::getEntityName(Entity entity) {
        return entityManager->getEntityName(entity);
    }

    void Coordinator::setEntityName(Entity entity, const std::string& name) {
        entityManager->setEntityName(entity, name);
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
        for (const Entity& entity : entityManager->getEntities()) {
            if (isEntityValid(entity)) {
                validEntities.push_back(entity);
            }
        }
        return validEntities;
    }

    Entity Coordinator::getEntity(std::string name) {
        for (Entity entity : entityManager->getEntities()) {
            if (this->getEntityName(entity) == name) {
                return entity;
            }
        }
        return INVALID_ENTITY;
    }

    Entity Coordinator::getEntityById(int id) {
        for (Entity entity : entityManager->getEntities()) {
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
        entityManager->setEntities(index, entity);
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
            std::cout << "Found handler for entity type: " << type << std::endl;
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

    bool Coordinator::hasComponent(Entity entity, ComponentType componentType)
    {
        return entityManager->getSignature(entity).test(componentType);
    }

    void Coordinator::updateSystems()
    {
        for (auto& [typeName, system] : this->getSystems()) {
            Signature systemSignature = this->getSystemSignature(typeName);
            for (auto currentEntity : system->entities) {
                Signature entitySignature = this->getEntitySignature(currentEntity);
                if ((entitySignature & systemSignature) == systemSignature) {
                    system->update(*this, currentEntity);
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
        //std::cout << "Event added: " << action << " for entity: " << id << std::endl;
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

    std::queue<std::pair<Entity, std::string>> Coordinator::getKilledQueue()
    {
        return _killedQueue;
    }

    void Coordinator::pushKilledQueue(std::pair<Entity, std::string> entity)
    {
        _killedQueue.push(entity);
    }

    void Coordinator::popKilledQueue()
    {
        _killedQueue.pop();
    }
}
