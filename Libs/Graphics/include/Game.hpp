/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#pragma once
#include "EntityFactory.hpp"

/**
 * @brief Namespace that contains all the graphics related classes
 * 
 * This namespace contains all the classes that are related to the graphics of the client.
 * 
 */
namespace Graphics {
    /// @brief Enum that define the state of the game
    /// @enum GameState
    enum class GameState {
        MENU,       // The menu state
        GAME,       // The game state
        PAUSE,      // The pause state
        SETTINGS,   // The settings state
        QUIT,       // The quit state
        GAMEOVER,   // The game over state
        WIN         // The win state
    };

    /// @brief Struct that define a star for the background
    /// @param x The x position of the star
    /// @param y The y position of the star
    /// @param size The size of the star
    /// @param color The color of the star
    struct Star {
        float x; // The x position of the star
        float y; // The y position of the star
        int size; // Size of the star
        Color color; // Color of the star
    };

    /**
     * @brief Game class that will handle the game loop
     * 
     * It provides functions to initialize the coordinator, set the game state, get the game state,
     * set the stars, draw the graphics, display the menu, display the game, display the pause menu,
     * and handle the keyboard input.
     * 
     */
    class Game {
        public:
            /// @brief Constructor of the game
            Game() : _gameState(GameState::MENU), _selected("") {}

            /// @brief Destructor of the game
            ~Game() {}

            /// @brief Initialize the coordinator with all of the entities
            void InitCoordinator();

            /// @brief Set the enum game state
            /// @param gameState The game state to set
            void setGameState(GameState gameState) { _gameState = gameState; }

            /// @brief Get the game state
            /// @return The game state that the game is in
            GameState getGameState() { return _gameState; }

            /// @brief Set the stars
            /// @param stars The stars to set
            void setStars(std::vector<Star> stars) { _stars = stars; }

            /** @brief Draw the stars of the background
             * 
             * This function is responsible for rendering stars in the game's graphical interface.
             */
            void DrawStars();

            /// @brief Draw the client graphics
            void DrawGraphics();

            /// @brief Display the menu
            void DrawMenu();

            /// @brief Display the game
            void DrawGame();

            /// @brief Display the pause menu
            void DrawPause();

            /// @brief Display the settings menu
            void DrawSettings();

            /// @brief Draw the settings titles
            void DrawSettingsTitles();

            /// @brief Draw the settings options
            void DrawSettingsOptions();

            /// @brief Handle the keyboard input
            void HandleKeyboardInput();

            /// @brief Handle the key 'space'
            void KeySpace();

            /// @brief Handle the key 'up' arrow
            void KeyUp();

            /// @brief Handle the key 'down' arrow
            void KeyDown();

            /// @brief Handle the key 'left' arrow
            void KeyLeft();

            /// @brief Handle the key 'right' arrow
            void KeyRight();

            /// @brief Handle the key 'escape'
            void KeyEscape();
        protected:
        private:
            /**
             * @brief The state of the game
             */
            GameState _gameState;

            /**
             * @brief The coordinator of the game
             * 
             * It will handle all the entities of the game.
             * 
             */
            ECS::Coordinator _coordinator;

            /**
             * @brief The stars of the background
             */
            std::vector<Star> _stars;

            /**
             * @brief Indicate that a string is hovered or selected
             * 
             * This will be used to change the color of rectangles when hovered or selected.
             */
            std::string _selected;
    };
}
