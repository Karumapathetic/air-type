/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawGame
*/

#include "Game.hpp"
#include "Draw.hpp"

namespace Graphics {
    void Game::DrawGame() {
        for (auto &star : _stars) {
            star.x -= 1.5f;
            if (star.x < 0) {
                star.x = GetScreenWidth();
                star.y = static_cast<float>(std::rand() % GetScreenHeight());
            }
        }
        DrawStars();
        DrawText("Game", 400, 200, 20, GRAY);
    }
} // namespace Graphics
