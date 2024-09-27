/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** settingsEntity.cpp
*/

#include "Settings.hpp"

namespace ECS {
    void settingsHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Keybind());
        gCoordinator.addComponent(entity, Sounds{LoadSound(""), 50, "Background Music" });
        Keybind& keybindComponent = gCoordinator.getComponent<Keybind>(entity);
        keybindComponent.addKeybind(KEY_SPACE, "Shoot", "Shoot");
        keybindComponent.addKeybind(KEY_UP, "Up", "Move Up");
        keybindComponent.addKeybind(KEY_DOWN, "Down", "Move Down");
        keybindComponent.addKeybind(KEY_LEFT, "Left", "Move Left");
        keybindComponent.addKeybind(KEY_RIGHT, "Right", "Move Right");
        keybindComponent.addKeybind(KEY_ESCAPE, "Pause", "Pause");
        gCoordinator.setEntityInitialized(entity, true);
    }
}
