/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#include <ctime>
#include "Game.hpp"

namespace Graphics {
    Game::Game() : _gameState(GameState::MENU)
    {
        _option = new Option(*this);
        _graphics = std::make_shared<RaylibGraphics>();
    }

    void Game::DrawSprites()
    {
        float scaleX = _graphics->GetWindowWidth() / MAX_X;
        float scaleY = _graphics->GetWindowHeight() / MAX_Y;
        float scale = std::min(scaleX, scaleY);
        for (auto entity : _entities) {
            if (entity.second.priority != -1.0f) {
                _graphics->RenderPreciseTexture(entity.second.texture, entity.second.crop, {entity.second.position.x * scale, entity.second.position.y * scale, entity.second.scale.x * scale, entity.second.scale.y * scale}, {0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    }

    void Game::AnimateEntity(Vector2 oldPos, Vector2 newPos, int id)
    {
        if (_entities[id].name == "player") {
            if (oldPos.y > newPos.y) {
                if (_entities[id].crop.x == _entities[id].crop.width * 4)
                    return;
                _entities[id].crop.x += _entities[id].crop.width;
            } else if (oldPos.y < newPos.y) {
                if (_entities[id].crop.x == 0)
                    return;
                _entities[id].crop.x -= _entities[id].crop.width;
            }
        } else if (_entities[id].name == "enemy") {
            if (_entities[id].crop.x == _entities[id].crop.width * 7)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        } else if (_entities[id].name == "missile") {
            if (_entities[id].crop.x == _entities[id].crop.width * 3)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }
    }

    void Game::DrawAddOns()
    {
        if (_option->getDisplayfps()) {
            _graphics->RenderFPS(10, 10);
        }
    }

    void Game::DrawGraphics()
    {
        _graphics->StartRendering();
        _graphics->ResetBackground(BLACK);
        HandleKeyboardInput();
        DrawAddOns();
        switch (getGameState()) {
            case Graphics::GameState::MENU:
                DrawMenu();
                break;
            case Graphics::GameState::GAME:
                DrawGame();
                break;
            case Graphics::GameState::PAUSE:
                DrawPause();
                break;
            case Graphics::GameState::SETTINGS:
                DrawSettings();
                break;
            case Graphics::GameState::GAMEOVER:
                break;
            case Graphics::GameState::WIN:
                break;
            default:
                break;
        }
        _graphics->EndRendering();
    }
}
