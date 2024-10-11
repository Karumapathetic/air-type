/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Keys
*/

#include "Option.hpp"

namespace Graphics {
    void Option::KeyShoot() {
        std::cout << "Shoot" << std::endl;
    }

    void Option::KeyUp() {
        std::cout << "Up" << std::endl;
    }

    void Option::KeyDown() {
        std::cout << "Down" << std::endl;
    }

    void Option::KeyLeft() {
        std::cout << "Left" << std::endl;
    }

    void Option::KeyRight() {
        std::cout << "Right" << std::endl;
    }

    void Option::KeyEscape() {
        switch (_game.getGameState()) {
            case GameState::GAME:
                _game.setGameState(GameState::PAUSE);
                break;
            case GameState::PAUSE:
                _game.setGameState(GameState::GAME);
                break;
            case GameState::SETTINGS:
                _game.setGameState(_game.getPreviousState());
                break;
            default:
                break;
        }
    }
} // namespace Graphics
