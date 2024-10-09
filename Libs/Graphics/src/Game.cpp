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
    Game::Game() : _gameState(GameState::MENU) {
        _option = new Option(*this);
    }

    void Game::InitTextures() {
        for (const auto& entity : _coordinator.getEntities()) {
            auto images = _coordinator.getComponent<ECS::Images>(entity);
            if (images.texture.id == 0 && _coordinator.getEntityName(entity) == "player") {
                std::cout << "Loading player texture..." << std::endl;
                images.texture = LoadTexture("Libs/Graphics/assets/texture/PlayerShip.gif");
            }
        }
    }

    void Game::DrawAddOns() {
        if (_option->getDisplayfps()) {
            DrawFPS(10, 10);
        }
    }

    void Game::DrawGraphics() {
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
