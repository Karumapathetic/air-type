/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#pragma once

namespace Graphics {
    enum class GameState {
        MENU,
        GAME,
        GAMEOVER
    };
    class Game {
        public:
            Game() { _gameState = GameState::MENU; }
            ~Game() {}
            void setGameState(GameState gameState) { _gameState = gameState; }
            GameState getGameState() { return _gameState; }
            int LaunchGame();
            void InitGraphics();
            void DrawGraphics();
            void DrawMenu();
            void DrawGame();
        protected:
        private:
            GameState _gameState;
    };
    int LaunchGame();
} // namespace Graphics