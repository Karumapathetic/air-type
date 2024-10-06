/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settingsEntity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        std::cout << "Step 1" << std::endl;
        gCoordinator.addComponent(entity, Keybind());
        std::cout << "Step 2" << std::endl;
        //gCoordinator.addComponent(entity, Sounds{LoadSound(""), 50, "Background Music" });
        std::cout << "Step 3" << std::endl;
        Keybind& keybindComponent = gCoordinator.getComponent<Keybind>(entity);
        keybindComponent.addKeybind(KEY_SPACE, "Shoot", "Shoot");
        keybindComponent.addKeybind(KEY_UP, "Up", "Move Up");
        keybindComponent.addKeybind(KEY_DOWN, "Down", "Move Down");
        keybindComponent.addKeybind(KEY_LEFT, "Left", "Move Left");
        keybindComponent.addKeybind(KEY_RIGHT, "Right", "Move Right");
        keybindComponent.addKeybind(KEY_ESCAPE, "Pause", "Pause");
        std::cout << "Step 4" << std::endl;
        gCoordinator.setEntityInitialized(entity, true);
    }
}
