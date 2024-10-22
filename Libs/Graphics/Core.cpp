/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Core
*/

#include "Core.hpp"

namespace Graphics {
    void Core::InitStars(int numStars) {
        std::srand(std::time(nullptr));
        std::vector<Graphics::Star> stars;
        for (int i = 0; i < numStars; ++i) {
            const Color colors[] = {WHITE, GRAY, LIGHTGRAY};
            stars.push_back({
                static_cast<float>(std::rand() % (int)MAX_X),
                static_cast<float>(std::rand() % _game.getGraphics()->GetWindowHeight()),
                std::rand() % 3 + 1,
                colors[std::rand() % 3]
                });
        }
        for (int i = 0; i < 5; ++i) {
            const Color colors[] = {RED, GREEN, BLUE, YELLOW, ORANGE};
            stars.push_back({
                static_cast<float>(std::rand() % (int)MAX_X),
                static_cast<float>(std::rand() % _game.getGraphics()->GetWindowHeight()),
                std::rand() % 3 + 4,
                colors[std::rand() % 5]
                });
        }
        _game.setStars(stars);
    }

    void Core::InitGame() {
        _game.getGraphics()->InitGraphics("Air-Type");
        _game.getGraphics()->SetFPS(60);
        InitStars(500);
        _game.setGameState(Graphics::GameState::MENU);
    }

    void Core::Caillou(bool *isRunning) {
        if (!_game.getGraphics()->IsWindowClosing() && _game.getGameState() != GameState::QUIT) {
            _game.DrawGraphics();
        } else {
            *isRunning = false;
        }
    }
}
