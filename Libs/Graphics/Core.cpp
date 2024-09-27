/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Core
*/

#include "Core.hpp"
#include "Game.hpp"

#include "raylib.h"


namespace Graphics {
    void Core::InitStars(int numStars) {
        std::srand(std::time(nullptr));
        std::vector<Graphics::Star> stars;
        for (int i = 0; i < numStars; ++i) {
            Color colors[] = {WHITE, GRAY, DARKGRAY};
            stars.push_back({
                static_cast<float>(std::rand() % GetScreenWidth()),
                static_cast<float>(std::rand() % GetScreenHeight()),
                std::rand() % 3 + 1,
                colors[std::rand() % 3]
                });
        }
        _game.setStars(stars);
    }

    void Core::InitGraphics() {
        int screenWidth = GetMonitorWidth(0);
        int screenHeight = GetMonitorHeight(0);
        InitWindow(screenWidth, screenHeight, "R-Type");
        SetTargetFPS(60);
        InitAudioDevice();
        SetExitKey(KEY_BACKSPACE);
        InitStars(120);
        _game.InitCoordinator();
    }

    void Core::CloseGraphics() {
        CloseWindow();
        CloseAudioDevice();
    }

    void Core::LaunchGame() {
        InitGraphics();

        // Main game loop
        while (!WindowShouldClose()) {
            _game.DrawGraphics();
        }

        CloseGraphics();
    }
}
