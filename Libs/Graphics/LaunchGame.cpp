/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** LaunchGame
*/

#include "raylib.h"
#include "EntityFactory.hpp"
#include "Game.hpp"

namespace Graphics {
    void Game::InitGraphics() {
        InitWindow(800, 600, "R-Type");
        SetTargetFPS(60);
        InitAudioDevice();
    }

    int Game::LaunchGame() {
        ECS::Coordinator = ECS::mainEngine();

        std::cout << "Hello client" << std::endl;
        while (!WindowShouldClose()) {
            BeginDrawing();
            DrawGraphics();
            EndDrawing();
        }

        CloseWindow();
        return 0;
    }

    void Game::DrawGraphics() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (getGameState()) {
            case MENU:
                DrawMenu();
                break;
            case GAME:
                DrawGame();
                break;
            default:
                break;
        }
        EndDrawing();
    }

    void Game::DrawMenu() {
        DrawText("Menu", 400, 200, 20, GRAY);
    }

    void Game::DrawGame() {
        DrawText("Game", 400, 200, 20, GRAY);
    }
}
