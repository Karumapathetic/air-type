/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Core
*/

#include "ICore.hpp"
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

/**
 * @brief Creates a new instance of the Core class.
 *
 * This function allocates memory for a new Core object and returns a pointer to it.
 * The caller is responsible for freeing the memory by calling DestroyCore() when
 * it is no longer needed.
 *
 * @return A pointer to a newly created Core object.
 */
EXPORT_API Graphics::Core* CreateCore() {
    return new Graphics::Core();
}

/**
 * @brief Destroys a Core object and frees the allocated memory.
 *
 * This function releases the memory allocated for the given Core object.
 * After calling this function, the caller should not use the Core object
 * anymore, as it may cause undefined behavior.
 *
 * @param core A pointer to the Core object to be destroyed.
 *
 * @return void
 */
EXPORT_API void DestroyCore(Graphics::ICore* core) {
    delete core;
}
