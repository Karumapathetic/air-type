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
    gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
    gCoordinator.addComponent(entity, Life{10.0f, 1.0f});
    gCoordinator.addComponent(entity, Speed{1.0f, 1.0f});
    gCoordinator.addComponent(entity, Images{ 0 , 1});
    gCoordinator.addComponent(entity, EntityTypes{std::string("player"), 1});
}

void ennemyHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
    gCoordinator.addComponent(entity, Speed{4.0f, 1.0f});
    gCoordinator.addComponent(entity, Images{ 0 , 1});
    gCoordinator.addComponent(entity, EntityTypes{std::string("ennemy"), 0});
}

void missileHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
    gCoordinator.addComponent(entity, Images{ 0 , 1});
    gCoordinator.addComponent(entity, EntityTypes{std::string("missile"), 0});
}

void backgroundHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Images{ 0 });
}

void settingsHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Keybind());
    gCoordinator.addComponent(entity, Sounds{ 0, std::string("Background Music") });
}

void collectibleHandler(Coordinator &gCoordinator, u_int32_t entity) {
    gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
    gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
    gCoordinator.addComponent(entity, Images{ 0 });
    gCoordinator.addComponent(entity, EntityTypes{std::string("collectible"), 1});
}

int mainEngine() {
    auto& gCoordinator = CoordinatorInstance::getInstance();

    // Init engine and register components and systems
    gCoordinator.init();
    gCoordinator.registerComponent<Spacial>();
    gCoordinator.registerComponent<Power>();
    gCoordinator.registerComponent<Life>();
    gCoordinator.registerComponent<Speed>();
    gCoordinator.registerComponent<Images>();
    gCoordinator.registerComponent<EntityTypes>();
    gCoordinator.registerComponent<Keybind>();
    gCoordinator.registerComponent<Sounds>();
    std::shared_ptr<ChangeValueSystem> changeValueSystem = gCoordinator.registerSystem<ChangeValueSystem>();

    // Create system(s) signature(s)
    Signature changeValueSignature;
    changeValueSignature.set(gCoordinator.getComponentType<Spacial>());
    gCoordinator.setSystemSignature<ChangeValueSystem>(changeValueSignature);

    std::vector<Entity> entities(MAX_ENTITIES);

    // Create entities
    for (int x = 0; x < 150; ++x) {
        entities[x] = gCoordinator.createEntity("player");
    }
    for (int x = 150; x < 300; ++x) {
        entities[x] = gCoordinator.createEntity("ennemy");
    }
    for (int x = 300; x < 450; ++x) {
        entities[x] = gCoordinator.createEntity("missile");
    }
    for (int x = 450; x < 600; ++x) {
        entities[x] = gCoordinator.createEntity("background");
    }
    for (int x = 600; x < 750; ++x) {
        entities[x] = gCoordinator.createEntity("settings");
    }
    for (int x = 750; x < 900; ++x) {
        entities[x] = gCoordinator.createEntity("collectible");
    }

    float newValue = 1.0f;
    for (const Entity& entity : entities) {
        std::string name = gCoordinator.getEntityName(entity);
        bool initialized = gCoordinator.getEntityInitialized(entity);

        // Depending on the entity type, initialize the entity
        std::unordered_map<std::string, std::function<void(Coordinator &gCoordinator, u_int32_t entity)>> handlers = {
            {"player", playerHandler},
            {"ennemy", ennemyHandler},
            {"missile", missileHandler},
            {"background", backgroundHandler},
            {"settings", settingsHandler},
            {"collectible", collectibleHandler}
        };
        if (handlers.find(name) != handlers.end() && initialized == 0) {
            handlers[name](gCoordinator, entity);
        }

        // Update entity with a system if it has Spacial component
        Signature entitySignature = gCoordinator.getEntitySignature(entity);
        if ((entitySignature & changeValueSignature) == changeValueSignature) {
            changeValueSystem->Update(newValue);
            Spacial& spacial = gCoordinator.getComponent<Spacial>(entity);
            std::cout << "Initialized : " << initialized << ". Entity: " << entity << ". Name: " << name << ". Spacial position : " << spacial.position << std::endl;
        } else {
            std::cout << "Initialized : " << initialized << ". Entity: " << entity << ". Name: " << name << " (no gravity)" << std::endl;
        }

        newValue += 1.0f;
    }

    return 0;
}
