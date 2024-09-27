/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Core
*/

#pragma once

#include "Game.hpp"
#include <iostream>
#include <ctime>

/// @brief Namespace for the graphics library
namespace Graphics {
    /// @brief Core class that will handle the core of the game
    class Core {
        public:
            Core() : _game() {}
            ~Core() {}
            /// @brief Initialize everything that the game needs
            void InitGraphics();
            /// @brief Close everything that the game needs
            void CloseGraphics();
            /// @brief Initialize the stars for the background
            void InitStars(int numStars);
            /// @brief Launch the game - Main loop of the game
            void LaunchGame();
        protected:
        private:
            Graphics::Game _game;
    };
}
