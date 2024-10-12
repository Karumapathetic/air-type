/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#pragma once
#include "Coordinator.hpp"
#include "Option.hpp"

/**
 * @brief Namespace that contains all the graphics related classes
 * 
 * This namespace contains all the classes that are related to the graphics of the client.
 * 
 */
namespace Graphics {
    class Option;
    /// @brief Enum that define the state of the game
    /// @enum GameState
    enum class GameState {
        MENU,       // The menu state
        GAME,       // The game state
        PAUSE,      // The pause state
        SETTINGS,   // The settings state
        QUIT,       // The quit state
        GAMEOVER,   // The game over state
        WIN,        // The win state
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
     * @brief Struct that holds data related to an entity in the game.
     * 
     * This struct is used to store the position, scale, texture, crop rectangle, and priority of an entity.
     * The constructor initializes the position to (0, 0), scale to (1, 1), texture to an empty Texture2D,
     * crop rectangle to (0, 0, 0, 0), and priority to 0.0f.
     */
    struct EntityData {
        Vector2 position;  ///< The position of the entity in the game world.
        Vector2 scale;     ///< The scale of the entity.
        Texture2D texture;  ///< The texture of the entity.
        Rectangle crop;    ///< The crop rectangle of the texture.
        float priority;    ///< The priority of the entity for rendering.

        /**
         * @brief Constructor of EntityData.
         * 
         * Initializes the position to (0, 0), scale to (1, 1), texture to an empty Texture2D,
         * crop rectangle to (0, 0, 0, 0), and priority to 0.0f.
         */
        EntityData(): position({0, 0}), scale({1, 1}), texture({}), crop({0, 0, 0, 0}), priority(0.0f) {}
    };

    using Entity = int;
    const int MAX_ENTITIES = 100;

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
            Game();

            /// @brief Destructor of the game
            ~Game() {}

            // void DrawSprites();

            /// @brief Set the enum game state
            /// @param gameState The game state to set
            void setGameState(GameState gameState) { _gameState = gameState; }

            /// @brief Get the game state
            /// @return The game state that the game is in
            GameState getGameState() { return _gameState; }

            /// @brief Get the previous state
            /// @return The previous state of the game
            GameState getPreviousState() { return _previousState; }

            /// @brief Set the stars
            /// @param stars The stars to set
            void setStars(std::vector<Star> stars) { _stars = stars; }

            std::string getClientAction() { return _clientAction; }

            void setClientAction(std::string clientAction) { _clientAction = clientAction; }

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

            /// @brief Draw add ons like FPS, etc.
            void DrawAddOns();

            /// @brief Handle the keyboard input
            void HandleKeyboardInput();

            /**
             * @brief Creates a new entity in the game.
             * 
             * This function initializes a new entity with the given ID and parameters.
             * The parameters are used to define the properties of the entity.
             * 
             * @param id The unique identifier for the new entity.
             * @param params A string containing the parameters for initializing the entity.
             * 
             * @return void
             */
            void CreateEntity(Entity id, const std::string& params);

            /**
             * @brief Updates the properties of an entity in the game.
             * 
             * This function takes an entity ID and a string of parameters to update the properties of the entity.
             * The parameters are used to define the new values for the entity's properties.
             * 
             * @param id The unique identifier for the entity to be updated.
             * @param params A string containing the parameters for updating the entity.
             * 
             * @return void
             */
            void UpdateEntity(Entity id, const std::string& params);

            /**
             * @brief Destroys the entity with the given ID from the game.
             * 
             * This function removes the entity with the specified ID from the game's coordinator.
             * It also releases any resources associated with the entity, such as textures or memory.
             * 
             * @param id The unique identifier for the entity to be destroyed.
             * 
             * @return void
             */
            void DestroyEntity(Entity id);

            /**
             * @brief Prints all the entities currently registered in the game.
             * 
             * This function iterates through the entities stored in the game's coordinator and prints their unique IDs,
             * positions, scales, textures, crop rectangles, and priorities. It is primarily used for debugging purposes.
             * 
             * @return void
             * 
             * @note This function does not return any meaningful value. It only prints the entities' information.
             */
            void PrintEntities();
        protected:
        private:
            /**
             * @brief The previous state of the game
             */
            GameState _previousState;

            /**
             * @brief The state of the game
             */
            GameState _gameState;


            std::vector<EntityData> entities;

            /**
             * @brief The stars of the background
             */
            std::vector<Star> _stars;

            /**
             * @brief The option of the game
             */
            Option *_option;

            /**
             * @brief The key that the client pressed (action)
             */
            std::string _clientAction;
    };
}
