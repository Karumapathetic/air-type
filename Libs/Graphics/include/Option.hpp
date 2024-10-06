/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Option
*/

#pragma once

#include "Game.hpp"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>

namespace Graphics {
    class Game;
    class Option {
        public:
            Option(Game& game);
            ~Option() {}

            void DrawSettingsOptions();

            void setSelected(std::string selected) { _selected = selected; }
            std::string getSelected() const { return _selected; }
            void setChanging(std::string changing) { _changing = changing; }
            std::string getChanging() const { return _changing; }
            std::unordered_map<std::string, int> getKeybinds() const { return _Keybinds; }
            void setKeybinds(std::unordered_map<std::string, int> keybinds) { _Keybinds = keybinds; }
            std::unordered_map<int, std::function<void()>> getBindedKeys() const { return _BindedKeys; }
            void setBindedKeys(std::unordered_map<int, std::function<void()>> bindedKeys) { _BindedKeys = bindedKeys; }

            /// @brief Handle the key 'space'
            void KeyShoot();

            /// @brief Handle the key 'up' arrow
            void KeyUp();

            /// @brief Handle the key 'down' arrow
            void KeyDown();

            /// @brief Handle the key 'left' arrow
            void KeyLeft();

            /// @brief Handle the key 'right' arrow
            void KeyRight();

            /// @brief Handle the key 'escape'
            void KeyEscape();

            /// @brief Draw the controls settings page
            void DrawControls();
        protected:
        private:
            std::unordered_map<int, std::function<void()>> _BindedKeys;
            std::unordered_map<std::string, int> _Keybinds;
            std::string _changing;
            Game& _game;

            /**
             * @brief Indicate that a string is hovered or selected
             * 
             * This will be used to change the color of rectangles when hovered or selected.
             */
            std::string _selected;
    };
} // namespace Graphics
