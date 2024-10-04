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
        for (const auto &star : _stars) {
            DrawCircle(static_cast<int>(star.x), static_cast<int>(star.y), star.size, star.color);
        }
        //auto drawSignature = _coordinator.getSystemSignature<ECS::Draw>();
        //for (auto& entity : _coordinator.getEntities()) {
        //    auto entitySignature = _coordinator.getEntitySignature(entity);
//
        //    if ((entitySignature & drawSignature) == drawSignature) {
        //        std::cout << "Le système Draw gère les entités avec un composant Images." << std::endl;
        //    } else {
        //        std::cout << "Le système Draw ne gère pas les entités avec un composant Images." << std::endl;
        //    }
        //}
        DrawText("Game", 400, 200, 20, GRAY);
        // DrawEntities();
    }
} // namespace Graphics
