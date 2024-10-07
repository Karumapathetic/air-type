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
            const Color colors[] = {WHITE, GRAY, DARKGRAY};
            stars.push_back({
                static_cast<float>(std::rand() % GetScreenWidth()),
                static_cast<float>(std::rand() % GetScreenHeight()),
                std::rand() % 3 + 1,
                colors[std::rand() % 3]
                });
        }
        stars[std::rand() % numStars].color = GREEN;
        stars[std::rand() % numStars].color = RED;
        stars[std::rand() % numStars].color = BLUE;
        _game.setStars(stars);
    }

    void Core::InitGraphics() {
        int screenWidth = GetMonitorWidth(0);
        int screenHeight = GetMonitorHeight(0);
        InitWindow(screenWidth, screenHeight, "R-Type");
        SetTargetFPS(60);
        InitAudioDevice();
        SetExitKey(KEY_BACKSPACE);
        InitStars(500);
        _game.InitCoordinator();
        _game.InitTextures();
    }

    void Core::CloseGraphics() {
        CloseWindow();
        CloseAudioDevice();
    }

    void Core::LaunchGame() {
        InitGraphics();

        const float fixedTimeStep = 1.0f / 60.0f;
        float accumulator = 0.0f;
        float lastTime = GetTime();

        // Main game loop
        while (!WindowShouldClose()) {
            float currentTime = GetTime();
            float frameTime = currentTime - lastTime;
            lastTime = currentTime;
            accumulator += frameTime;

            while (accumulator >= fixedTimeStep) {
                accumulator -= fixedTimeStep;
            }

            _game.DrawGraphics(); // Render the game state
        }

        CloseGraphics();
    }
}
