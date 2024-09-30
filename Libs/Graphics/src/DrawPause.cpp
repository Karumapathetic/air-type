/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawPause
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawPause() {
        for (const auto &star : _stars) {
            DrawCircle(static_cast<int>(star.x), static_cast<int>(star.y), star.size, star.color);
        }
        DrawText("PAUSE", GetScreenWidth() / 2 - MeasureText("PAUSE", 40) / 2, GetScreenHeight() / 2 - 40, 40, WHITE);
    }
}
