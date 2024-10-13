/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settingsEntity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Keybind());
        //gCoordinator.addComponent(entity, Sounds{LoadSound(""), 50, "Background Music" });
        Keybind& keybindComponent = gCoordinator.getComponent<Keybind>(entity);
        keybindComponent.addKeybind(265, "Up", "Move Up");
        keybindComponent.addKeybind(264, "Down", "Move Down");
        keybindComponent.addKeybind(263, "Left", "Move Left");
        keybindComponent.addKeybind(262, "Right", "Move Right");
        keybindComponent.addKeybind(32, "Shoot", "Shoot/Select");
        keybindComponent.addKeybind(256, "Pause", "Pause/Unpause");
        gCoordinator.setEntityInitialized(entity, true);
    }
}
