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
            star.x -= 1.0f;
            if (star.x < 0) {
                star.x = _graphics->GetWindowWidth();
                star.y = static_cast<float>(std::rand() % _graphics->GetWindowHeight());
            }
        }
        DrawStars();
        DrawSprites();
    }
} // namespace Graphics
