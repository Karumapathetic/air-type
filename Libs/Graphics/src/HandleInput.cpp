/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** HandleInput
*/

#include "Game.hpp"

namespace Graphics {
    void Game::HandleKeyboardInput() {
        int key = GetKeyPressed();
        if (key != 0) {
            auto keyHandlers = _option->getBindedKeys();
            if (_option->getChanging() == "" && keyHandlers.find(key) != keyHandlers.end()) {
                keyHandlers[key]();
            }
            if (_option->getChanging() != "") {
                std::string oldAction = _option->getChanging();
                auto& keybinds = getCoordinator().getComponent<ECS::Keybind>(getCoordinator().getEntity("settings")).keybinds;
                int oldKey = keybinds[oldAction].first;
                std::cout << "Key pressed: " << key << std::endl;
                std::cout << "Old action: " << oldAction << std::endl;
                std::cout << "Old key: " << oldKey << std::endl;
                keybinds[oldAction] = std::make_pair((KeyboardKey)key, keybinds[oldAction].second);
                std::function<void()> handler = keyHandlers[oldKey];
                keyHandlers.erase(oldKey);
                keyHandlers[key] = handler;
                _option->setBindedKeys(keyHandlers);
                _option->setChanging("");
            }
        }
    }
} // namespace Graphics
