/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IGame
*/

// IGame.hpp
#pragma once

#include <vector>
#include <string>
#include <memory>

#include "IGraphic.hpp"

#ifdef _WIN32
    #define EXPORT_API extern "C" __declspec(dllexport)
#else
    #define EXPORT_API extern "C"
#endif


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
        WIN,        // The win state
    };

    /**
     * @brief Struct that holds data related to an entity in the game.
     * 
     * This struct is used to store the position, scale, texture, crop rectangle, and priority of an entity.
     * The constructor initializes the position to (0, 0), scale to (1, 1), texture to an empty Texture2D,
     * crop rectangle to (0, 0, 0, 0), and priority to 0.0f.
     */
    struct EntityData {
        std::string name;  ///< The name of the entity.
        Vector2 position;  ///< The position of the entity in the game world.
        Vector2 scale;     ///< The scale of the entity.
        Rectangle crop;    ///< The crop rectangle of the texture.
        float priority;    ///< The priority of the entity for rendering.

        /**
         * @brief Constructor of EntityData.
         * 
         * Initializes the position to (0, 0), scale to (1, 1), texture to an empty Texture2D,
         * crop rectangle to (0, 0, 0, 0), and priority to 0.0f.
         */
        EntityData(): name(""), position({0, 0}), scale({1, 1}), crop({0, 0, 0, 0}), priority(-1.0f) {}
    };

    class IGame {
    public:
        virtual ~IGame() = default;

        virtual void setGameState(GameState gameState) = 0;
        virtual GameState getGameState() const = 0;
        virtual void setStars(std::vector<Star> stars) = 0;
        virtual void DrawStars() const = 0;
        virtual void DrawGraphics() = 0;
        virtual void HandleKeyboardInput() = 0;
        virtual void CreateEntity(Entity id, const std::string& params) = 0;
        virtual void UpdateEntity(Entity id, const std::string& params) = 0;
        virtual void DestroyEntity(Entity id) = 0;
        virtual float GetNumberOfClients() const = 0;
        virtual std::shared_ptr<IGraphic> getGraphics() const = 0;
        virtual std::vector<std::string> getClientAction() const = 0;
        virtual EntityData &getEntity(int &Id) = 0;
    };
}