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
#include "Draw.hpp"

namespace Graphics {
    Game::Game() : _gameState(GameState::MENU), entities(MAX_ENTITIES)
    {
        _option = new Option(*this);
    }

    void Game::DrawSprites()
    {
        for (EntityData entity : entities) {
            if (entity.priority != -1.0f) {
                DrawTexturePro(entity.texture, entity.crop, {entity.position.x, entity.position.y, entity.scale.x, entity.scale.y}, {0.0f, 0.0f}, 0.0f, WHITE);
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
