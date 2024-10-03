/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawSettings
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawSettings() {
        Rectangle rec_option = {
            (float)GetScreenWidth() / 2 - 100,
            (float)GetScreenHeight() / 3,
            (float)GetScreenWidth() / 10,
            (float)GetScreenHeight() / 20
        };
        DrawStars();
        DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 25) / 2, rec_option.y - 50, 25, WHITE);
    }
} // namespace Graphics
