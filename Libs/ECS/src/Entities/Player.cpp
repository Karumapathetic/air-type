/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** playerEntity
*/

#include "Coordinator.hpp"

namespace ECS {
    void playerHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        std::cout << "Step 1" << std::endl;
        gCoordinator.addComponent(entity, Spacial{1.0f, 0.0f});
        std::cout << "Step 2" << std::endl;
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        std::cout << "Step 3" << std::endl;
        gCoordinator.addComponent(entity, Life{10.0f, 1.0f});
        std::cout << "Step 4" << std::endl;
        gCoordinator.addComponent(entity, Speed{1.0f, 1.0f});
        std::cout << "Step 5" << std::endl;
        gCoordinator.addComponent(entity, Images{0});
        std::cout << "Step 6" << std::endl;
        gCoordinator.addComponent(entity, EntityTypes{"player", 1});
        std::cout << "Step 7" << std::endl;
        gCoordinator.setEntityInitialized(entity, true);
    }
}
