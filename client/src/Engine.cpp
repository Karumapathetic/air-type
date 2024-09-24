/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client engine
*/

#include "Engine.hpp"

class ChangeValueSystem : public ISystem {
public:
    void Update(float newPos) {
        auto& gCoordinator = CoordinatorInstance::getInstance();
        for (auto& entity : entities) {
            auto& spacial = gCoordinator.getComponent<Spacial>(entity);
            spacial.position = newPos;
        }
    }
};

void playerHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Life{1.0f, 1.0f});
    gCoordinator.addComponent(entity, Speed{1.0f, 1.0f});
    gCoordinator.addComponent(entity, Images{ 0 , 1});
    gCoordinator.addComponent(entity, EntityTypes{"player", 1});
}

int mainEngine() {
    auto& gCoordinator = CoordinatorInstance::getInstance();

    gCoordinator.init();
    gCoordinator.registerComponent<Spacial>();
    gCoordinator.registerComponent<Power>();
    gCoordinator.registerComponent<Life>();
    gCoordinator.registerComponent<Speed>();
    gCoordinator.registerComponent<Images>();
    gCoordinator.registerComponent<EntityTypes>();
    auto changeValueSystem = gCoordinator.registerSystem<ChangeValueSystem>();

    Signature signature;
    signature.set(gCoordinator.getComponentType<Spacial>());
    gCoordinator.setSystemSignature<ChangeValueSystem>(signature);

    std::vector<Entity> entities(MAX_ENTITIES);

    for (int x = 0; x < 250; ++x) {
        auto entity = gCoordinator.createEntity("player");
        entities[x] = entity;
    }

    for (int x = 250; x < MAX_ENTITIES; ++x) {
        entities[x] = gCoordinator.createEntity("Empty");
    }

    float newForce = 1.0f;
    for (const auto& entity : entities) {
        std::string name = gCoordinator.getEntityName(entity);
        bool initialized = gCoordinator.getEntityInitialized(entity);
        std::unordered_map<std::string, std::function<void(Coordinator &gCoordinator, u_int32_t entity)>> handlers = {
            {"player", playerHandler}
        };

        if (handlers.find(name) != handlers.end() && initialized == 0) {
            handlers[name](gCoordinator, entity);
        } else {
        }
        Signature entitySignature = gCoordinator.getEntitySignature(entity);
        if ((entitySignature & signature) == signature) {
            changeValueSystem->Update(newForce);
            Spacial& spacial = gCoordinator.getComponent<Spacial>(entity);
            std::cout << "Initialized : " << initialized << ". Entity: " << entity << ". Name: " << name << ". Spacial position : " << spacial.position << std::endl;
        } else {
            std::cout << "Initialized : " << initialized << ". Entity: " << entity << ". Name: " << name << " (no gravity)" << std::endl;
        }

        newForce += 1.0f;
    }

    return 0;
}
