/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#include <iostream>
#include <ctime>
#include "raylib.h"
#include "Game.hpp"

namespace Graphics {
    Game::Game() : _gameState(GameState::MENU), entities(MAX_ENTITIES)
    {
        _option = new Option(*this);
    }

    void Game::DrawSprites()
    {
        float scaleX = GetScreenWidth() / MAX_X;
        float scaleY = GetScreenHeight() / MAX_Y;
        float scale = std::min(scaleX, scaleY);
        for (EntityData entity : entities) {
            if (entity.priority != -1.0f) {
                DrawTexturePro(entity.texture, entity.crop, {entity.position.x * scale, entity.position.y * scale, entity.scale.x * scale, entity.scale.y * scale}, {0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    }

    void Game::DrawAddOns()
    {
        if (_option->getDisplayfps()) {
            DrawFPS(10, 10);
        }
    }

    void Game::DrawGraphics()
    {
        BeginDrawing();
        ClearBackground(BLACK);
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
        EndDrawing();
    }
}
