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

            /**
             * @brief Constructs an Option object.
             * 
             * This constructor initializes an Option object with a reference to a Game object.
             * 
             * @param game A reference to the Game object that this Option will be associated with.
             */
            Option(Game& game);

            /**
             * @brief Destroys the Option object.
             * 
             * This destructor destroys the Option object.
             */
            ~Option() {}

            /**
             * @brief Set the selected string
             * 
             * This function sets the selected string.
             * 
             * @param selected The string to set as selected.
             */
            void setSelected(std::string selected) { _selected = selected; }

            /**
             * @brief Get the selected string
             * 
             * This function returns the selected string.
             * 
             * @return The selected string.
             */
            std::string getSelected() const { return _selected; }

            /**
             * @brief Set the changing string that is used to know which key is being changed
             * 
             * @param changing The string to set as changing.
             */
            void setChanging(std::string changing) { _changing = changing; }

            /**
             * @brief Get the changing string that is used to know which key is being changed
             * 
             * @return The changing string.
             */
            std::string getChanging() const { return _changing; }

            /**
             * @brief Get the binded keys
             * 
             * This function returns an unordered map of binded keys.
             * We use this to bind keys to functions.
             * 
             * @return The binded keys.
             */
            std::unordered_map<int, std::function<void()>> getBindedKeys() const { return _BindedKeys; }

            /**
             * @brief Set the binded keys
             * 
             * This function sets the binded keys.
             * 
             * @param bindedKeys The binded keys to set.
             */
            void setBindedKeys(std::unordered_map<int, std::function<void()>> bindedKeys) { _BindedKeys = bindedKeys; }

            /**
             * @brief Get the keybinds
             * 
             * This function returns an unordered map of keybinds.
             * 
             * @return The keybinds.
             */
            std::unordered_map<std::string, std::pair<int, std::string>> getKeybinds() const { return _keybinds; }

            /**
             * @brief Set the keybinds
             * 
             * This function sets the keybinds.
             * 
             * @param keybinds The keybinds to set.
             */
            void setKeybinds(std::unordered_map<std::string, std::pair<int, std::string>> keybinds) { _keybinds = keybinds; }

            /**
             * @brief Set the displayfps boolean
             * 
             * This function sets the displayfps boolean.
             * 
             * @param displayfps The boolean to set as displayfps.
             */
            bool getDisplayfps() const { return _displayfps; }

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

            /// @brief Draw the settings options
            void DrawSettingsOptions();

            /// @brief Draw the video settings page
            void DrawVideoSettings();

            /// @brief Draw the controls settings page
            void DrawControlsSettings();
        protected:
        private:
            /**
             * @brief The binded keys
             */
            std::unordered_map<int, std::function<void()>> _BindedKeys;

            /**
             * @brief The keybinds
             */
            std::unordered_map<std::string, std::pair<int, std::string>> _keybinds;

            /**
             * @brief The changing string that is used to know which key is being changed
             */
            std::string _changing;

            /**
             * @brief The displayfps boolean
             */
            bool _displayfps;

            /**
             * @brief A reference to the Game object
             */
            Game& _game;

            /**
             * @brief Indicate that a string is hovered or selected
             * 
             * This will be used to change the color of rectangles when hovered or selected.
             */
            std::string _selected;
    };
} // namespace Graphics
