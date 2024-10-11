/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Core
*/

#pragma once

#include "Game.hpp"
#include <iostream>
#include <ctime>

namespace Graphics {
    /**
     * @brief Core class that will handle the game loop
     * 
     * It provides functions to initialize the graphics, close the graphics, initialize the stars,
     * and launch the game.
     */
    class Core {
        public:
            /**
             * @brief Construct a new Core object
             * 
             * This constructor initializes the game object.
             */
            Core() : _game() {}

            /**
             * @brief Destroy the Core object
             * 
             * This destructor destroys the game object.
             */
            ~Core() {}

            /**
             * @brief Initialize the graphics.
             * 
             * It initializes the graphics by setting the window size, the window title, and the background color.
             * As well as setting the target FPS and the number of stars.
             */
            void InitGraphics();

            /**
             * @brief Close the graphics.
             * 
             * It closes the graphics by closing the window and stops the audio.
             */
            void CloseGraphics();

            /**
             * @brief Initialize the stars for the star field.
             * 
             * It initializes the stars by setting the number of stars and creating the stars.
             * Also adds some random planets.
             * 
             * @param numStars The number of stars.
             */
            void InitStars(int numStars);

            /**
             * @brief Launch the game.
             * 
             * It starts the game loop.
             */
            void Caillou(bool *isRunning);
        protected:
        private:
            /**
             * @brief The game object.
             */
            Graphics::Game _game;
    };
}
