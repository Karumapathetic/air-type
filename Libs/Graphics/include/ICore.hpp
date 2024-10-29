/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ICore
*/

#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

#include "IGame.hpp"

namespace Graphics {
    class ICore {
    public:
        virtual ~ICore() = default;

        /**
         * @brief Initializes the game.
         * This method should set up the game environment and any necessary resources.
         */
        virtual void InitGame() = 0;

        /**
         * @brief Initializes the stars.
         * This method should create the specified number of stars and add them to the game environment.
         *
         * @param numStars The number of stars to initialize.
         */
        virtual void InitStars(int numStars) = 0;

        /**
         * @brief Handles the Caillou game logic.
         * This method should update the game state based on the Caillou game rules and handle user input.
         *
         * @param isRunning A pointer to a boolean flag indicating whether the game is running.
         *                  The method should update this flag to false when the game ends.
         */
        virtual void Caillou(bool *isRunning) = 0;

        /**
         * @brief Retrieves a reference to the game instance.
         * This method should return a reference to the game instance, allowing access to game-specific methods and data.
         *
         * @return A reference to the game instance.
         */
        virtual IGame& getGame() = 0;
    };
}

#endif // ICORE_HPP
