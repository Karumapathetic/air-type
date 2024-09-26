/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** LaunchGame
*/

#include <iostream>
#include "raylib.h"
#include "Game.hpp"

namespace Graphics {
    void Game::InitGraphics() {
        int screenWidth = GetMonitorWidth(0);
        int screenHeight = GetMonitorHeight(0);
        InitWindow(screenWidth, screenHeight, "R-Type");
        SetTargetFPS(60);
        InitAudioDevice();
        SetExitKey(KEY_BACKSPACE);
    }

    int Game::LaunchGame() {
        ECS::Coordinator coord = ECS::mainEngine();
        InitGraphics();

        std::cout << "Hello client" << std::endl;
        while (!WindowShouldClose()) {
            DrawGraphics();
        }

        CloseWindow();
        CloseAudioDevice();
        return 0;
    }

    void Game::DrawGraphics() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        switch (getGameState()) {
            case Graphics::GameState::MENU :
                DrawMenu();
                break;
            case Graphics::GameState::GAME:
                DrawGame();
                break;
            default:
                break;
        }
        EndDrawing();
    }
}

/*
Doit faire HandleKey
Mettre premiers sound
Chercher parallax star-field
*/
