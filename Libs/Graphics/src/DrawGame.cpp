/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawGame
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawGame() {
        for (auto &star : _stars) {
            star.x -= 1.5f;
            if (star.x < 0) {
                star.x = GetScreenWidth();
                star.y = static_cast<float>(std::rand() % GetScreenHeight());
            }
        }
        for (const auto &star : _stars) {
            DrawCircle(static_cast<int>(star.x), static_cast<int>(star.y), star.size, star.color);
        }
        DrawText("Game", 400, 200, 20, GRAY);
        // DrawEntities();
    }
} // namespace Graphics
