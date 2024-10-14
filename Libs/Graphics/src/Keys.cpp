/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Keys
*/

#include "Option.hpp"

namespace Graphics {
    void Option::KeyShoot() {
        _game.setClientAction("shoot");
    }

    void Option::KeyUp() {
        _game.setClientAction("up");
    }

    void Option::KeyDown() {
        _game.setClientAction("down");
    }

    void Option::KeyLeft() {
        _game.setClientAction("left");
    }

    void Option::KeyRight() {
        _game.setClientAction("right");
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
        _game.setClientAction("escape");
    }
} // namespace Graphics
