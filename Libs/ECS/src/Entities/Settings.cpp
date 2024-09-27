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
        gCoordinator.addComponent(entity, Sounds{LoadSound(""), 0, "Background Music" });
        Keybind& keybindComponent = gCoordinator.getComponent<Keybind>(entity);
        keybindComponent.addKeybind(KEY_ENTER, "validate", "Confirm action");
        gCoordinator.setEntityInitialized(entity, true);
    }
}
