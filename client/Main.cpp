#include <iostream>
#include <vector>
#include "Coordinator.hpp"

struct Gravity {
    float force;
};

int main() {

    Coordinator gCoordinator;
    gCoordinator.Init();
    gCoordinator.RegisterComponent<Gravity>();

    Signature signature;
    signature.set(gCoordinator.GetComponentType<Gravity>());

    std::vector<Entity> entities(MAX_ENTITIES);

    for (auto& entity : entities) {
        entity = gCoordinator.CreateEntity("test");
        gCoordinator.AddComponent(entity, Gravity{10.0f});
    }

    for (const auto& entity : entities) {
        Gravity& gravity = gCoordinator.GetComponent<Gravity>(entity);
        std::cout << "Entity: " << entity << " Gravity force: " << gravity.force << std::endl;
    }
    return 0;
}