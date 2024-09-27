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
    void Game::InitCoordinator() {
        _coordinator = ECS::mainEngine();
    }

    void Game::DrawGraphics() {
        BeginDrawing();
        switch (getGameState()) {
            case Graphics::GameState::MENU :
                ClearBackground(RAYWHITE);
                DrawMenu();
                break;
            case Graphics::GameState::GAME:
                ClearBackground(BLACK);
                DrawGame();
                break;
            default:
                break;
        }
        EndDrawing();
    }
}
