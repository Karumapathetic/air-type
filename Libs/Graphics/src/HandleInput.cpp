/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** HandleInput
*/

#include "Game.hpp"

namespace Graphics {
    void Game::HandleKeyboardInput() {
        _clientAction.clear();
        auto keyHandlers = _option->getBindedKeys();
        for (int key = KEY_SPACE; key <= KEY_KP_EQUAL; ++key) {
            if (IsKeyDown(key)) {
                if (_option->getChanging() == "" && keyHandlers.find(key) != keyHandlers.end()) {
                    keyHandlers[key]();
                }
                if (!_option->getChanging().empty()) {
                    std::string oldAction = _option->getChanging();
                    auto keybinds = _option->getKeybinds();
                    int oldKey = keybinds[oldAction].first;
                    keybinds[oldAction] = std::make_pair((KeyboardKey)key, keybinds[oldAction].second);
                    _option->setKeybinds(keybinds);
                    std::function<void()> handler = keyHandlers[oldKey];
                    keyHandlers.erase(oldKey);
                    keyHandlers[key] = handler;
                    _option->setBindedKeys(keyHandlers);
                    _option->setChanging("");
                }
            }
        }
    }
} // namespace Graphics
