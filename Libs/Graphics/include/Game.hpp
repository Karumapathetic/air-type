/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#pragma once
#include "EntityFactory.hpp"

namespace Graphics {
    /// @brief Enum that define the state of the game
    enum class GameState {
        MENU,
        GAME,
        PAUSE,
        GAMEOVER,
        WIN
    };
    /// @brief Struct that define a star for the background
    struct Star {
        float x, y;
        int size;
        Color color;
    };

    /// @brief Game class that will handle the game state
    class Game {
        public:
            Game() : _gameState(GameState::MENU) {}
            ~Game() {}
            /// @brief Initialize the coordinator
            void InitCoordinator();

            /// @brief Set the game state
            /// @param gameState The game state to set
            void setGameState(GameState gameState) { _gameState = gameState; }

            /// @brief Get the game state
            /// @return The game state
            GameState getGameState() { return _gameState; }

            /// @brief Set the stars
            /// @param stars The stars to set
            void setStars(std::vector<Star> stars) { _stars = stars; }

            /// @brief Draw the client graphics
            void DrawGraphics();

            /// @brief Draw the menu
            void DrawMenu();

            /// @brief Draw the game
            void DrawGame();

            /// @brief Draw the pause
            void DrawPause();

            /// @brief Handle the keyboard input
            void HandleKeyboardInput();

            /// @brief Handle the key space
            void KeySpace();

            /// @brief Handle the key up
            void KeyUp();

            /// @brief Handle the key down
            void KeyDown();

            /// @brief Handle the key left
            void KeyLeft();

            /// @brief Handle the key right
            void KeyRight();

            /// @brief Handle the key escape
            void KeyEscape();
        protected:
        private:
            GameState _gameState;
            ECS::Coordinator _coordinator;
            std::vector<Star> _stars;
    };
} // namespace Graphics
