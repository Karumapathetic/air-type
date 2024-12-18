/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#pragma once

#include "Option.hpp"
#include "Raylib.hpp"
#include "IGame.hpp"

#include <iostream>
#include <functional>
#include <memory>
#include <chrono>

#define MAX_X 1920.0f
#define MAX_Y 1080.0f

/**
 * @brief Namespace that contains all the graphics related classes
 * 
 * This namespace contains all the classes that are related to the graphics of the client.
 * 
 */
namespace Graphics {
    class Option;

    /**
     * @brief Game class that will handle the game loop
     * 
     * It provides functions to initialize the coordinator, set the game state, get the game state,
     * set the stars, draw the graphics, display the menu, display the game, display the pause menu,
     * and handle the keyboard input.
     * 
     */
    class Game : public IGame{
        public:
            /// @brief Constructor of the game
            Game();

            /// @brief Destructor of the game
            ~Game() {}

            /// @brief Set the enum game state
            /// @param gameState The game state to set
            void setGameState(GameState gameState) override { _gamestate.first = _gamestate.second; _gamestate.second = gameState; }

            /// @brief Get the game state
            /// @return The game state that the game is in
            GameState getGameState() const override { return _gamestate.second; }

            /// @brief Get the previous state
            /// @return The previous state of the game
            GameState getPreviousState() const { return _gamestate.first; }

            /// @brief Set the stars
            /// @param stars The stars to set
            void setStars(std::vector<Star> stars) override { _stars = stars; }

            /**
             * @brief Get the Client Action object
             * 
             * @return std::vector<std::string> 
             */
            std::vector<std::string> getClientAction() const override { return _clientAction; }

            /**
             * @brief Add a client action to the vector client action
             * 
             * @param clientAction The client action to add
             */
            void addClientAction(std::string clientAction) { _clientAction.push_back(clientAction); }

            /**
             * @brief Get the Graphics object
             * 
             * @return std::shared_ptr<IGraphic> 
             */
            std::shared_ptr<IGraphic> getGraphics() const override { return _graphics; }

            /** @brief Draw the stars of the background
             * 
             * This function is responsible for rendering stars in the game's graphical interface.
             */
            void DrawStars() const override;

            /// @brief Draw the client graphics
            void DrawGraphics() override;

            /// @brief Display the menu
            void DrawMenu();

            /// @brief Display the game
            void DrawGame();

            /// @brief Display the pause menu
            void DrawPause();

            /// @brief Display the settings menu
            void DrawSettings();

            /// @brief Draw the rectangle background of the settings
            void DrawRectangleBackground() const;

            /// @brief Draw the settings titles
            void DrawSettingsTitles();

            /// @brief Draw add ons like FPS, etc.
            void DrawAddOns() const;

            /// @brief Draw all the entities
            void DrawSprites();

            /// @brief Handle the keyboard input
            void HandleKeyboardInput() override;

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
            void CreateEntity(Entity id, const std::string& params) override;

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
            void UpdateEntity(Entity id, const std::string& params) override;

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
            void DestroyEntity(Entity id) override;

            /**
             * @brief Animates an entity from its old position to its new position.
             * 
             * This function takes the old and new positions of an entity and animates it from the old position to the new position.
             * The entity's texture is updated based on the direction of movement.
             * 
             * @param oldPos The old position of the entity.
             * @param newPos The new position of the entity.
             * @param id The unique identifier of the entity to animate.
             */
            void AnimateEntity(Vector2 oldPos, Vector2 newPos, int id);

            void AnimationsMap(int id, Vector2 oldPos, Vector2 newPos);

            /**
             * @brief Get the Number Of Clients already inGame
             * 
             * @return The number of clients in the game
             */
            float GetNumberOfClients() const override;

            EntityData &getEntity(int &Id) override { return _entities[Id]; }
        protected:
        private:
            /**
             * @brief The state of the game
             * 
             * First state is the previous game state
             * Second state is the current game state
             */
            std::pair<GameState, GameState> _gamestate;

            /**
             * @brief The entities of the game
             */
            std::unordered_map<int, EntityData> _entities;

            /**
             * @brief The stars of the background
             */
            std::vector<Star> _stars;

            /**
             * @brief The option of the game
             */
            Option *_option;

            /**
             * @brief The keys that the client pressed (actions)
             */
            std::vector<std::string> _clientAction;

            /**
             * @brief The graphics object
             */
            std::shared_ptr<IGraphic> _graphics;

            /**
             * @brief The animations for the entities
             */
            std::unordered_map<int, std::chrono::steady_clock::time_point> _animationMap;
    };
}
