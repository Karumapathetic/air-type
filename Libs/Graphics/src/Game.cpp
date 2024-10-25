/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#include <ctime>
#include "Game.hpp"

namespace Graphics {
    Game::Game() : _gamestate(std::make_pair(GameState::MENU, GameState::MENU))
    {
        _option = new Option(*this);
        _graphics = std::make_shared<RaylibGraphics>();
        InitializeAnimationsMap();
    }

    void Game::DrawSprites()
    {
        float scaleX = _graphics->GetWindowWidth() / MAX_X;
        float scaleY = _graphics->GetWindowHeight() / MAX_Y;
        float scale = std::min(scaleX, scaleY);
        for (auto entity : _entities) {
            if (entity.second.priority != -1.0f) {
                _graphics->RenderPreciseTexture(entity.first, entity.second.crop, {entity.second.position.x * scale, entity.second.position.y * scale, entity.second.scale.x * scale, entity.second.scale.y * scale}, {0.0f, 0.0f}, 0.0f, WHITE);
                if (entity.second.name == "killed")
                    AnimateEntity(entity.second.position, entity.second.position, entity.first);
            }
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
