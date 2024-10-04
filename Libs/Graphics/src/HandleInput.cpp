/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** HandleInput
*/

#include "Game.hpp"

namespace Graphics {
    void Game::HandleKeyboardInput() {
        switch (GetKeyPressed()) {
            case KEY_SPACE:
                KeySpace();
                break;
            case KEY_UP:
                KeyUp();
                break;
            case KEY_DOWN:
                KeyDown();
                break;
            case KEY_LEFT:
                KeyLeft();
                break;
            case KEY_RIGHT:
                KeyRight();
                break;
            case KEY_ESCAPE:
                KeyEscape();
                break;
            default:
                break;
        }
    }

    void Game::KeySpace() {
        if (_gameState == GameState::MENU) {
            setGameState(GameState::GAME);
        }
    }

    void Game::KeyUp() {
        std::cout << "Up" << std::endl;
    }

    void Game::KeyDown() {
        std::cout << "Down" << std::endl;
    }

    void Game::KeyLeft() {
        std::cout << "Left" << std::endl;
    }

    void Game::KeyRight() {
        std::cout << "Right" << std::endl;
    }

    void Game::KeyEscape() {
        switch (_gameState) {
            case GameState::GAME:
                setGameState(GameState::PAUSE);
                break;
            case GameState::PAUSE:
                setGameState(GameState::GAME);
                break;
            case GameState::SETTINGS:
                setGameState(GameState::PAUSE);
                break;
            default:
                break;
        }
    }
} // namespace Graphics
