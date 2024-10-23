/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawStars
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawStars() {
        for (const auto &star : _stars) {
            _graphics->RenderCircle(static_cast<int>(star.x), static_cast<int>(star.y), star.size, star.color);
        }
    }
}
