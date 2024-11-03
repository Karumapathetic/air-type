/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** RequestsTypes
*/

#pragma once

#include <cstdint>

/**
 * @brief Namespace for Network library
 * 
 * This namespace contains all the classes and functions for the Network library.
 */
namespace Network {

    /// @brief Enum that define every types of requests
    /// @enum RequestsTypes
    enum class RequestsTypes : uint32_t
    {
        ClientConnection = 0,       // The Client try to connect
        ClientDisconnection = 1,    // The Client try to disconnect
        ServerPing = 2,             // The Client ping the server
        ServerAcceptance = 3,       // The Server accept Client connection
        ServerDenial = 4,           // The Server refuse Client connection
        AcknowledgeRequest = 5,     // The Server or Client acknowledge previous request
        SetSpritePosition = 6,      // The Server send a sprite positions
        NotifyKilledSprite = 7,     // The Server notify a entity is killed
        SetInput = 8,               // The Client send user input to Server
        LaunchGame = 9              // The Server launch the game
    };

    /// @brief Enum that define every types of sprites
    /// @enum SpritesTypes
    enum class SpritesTypes : uint32_t
    {
        Player = 0,         // Player type
        PataPata = 1,       // Pata-Pata type
        Win = 2,            // Win type
        Wick = 3,           // Wick type
        Geld = 4,           // Geld type
        Bug = 5,            // Bug type
        Missile = 6,        // Missile type
        Default = 7         // Default type
    };

    /// @brief Enum that define every types of actions
    /// @enum InputActions
    enum class InputActions : uint32_t
    {
        UP = 0,         // Player goes up
        DOWN = 1,       // Player goes down
        LEFT = 2,       // Player goes left
        RIGHT = 3,      // Player goes right
        SHOOT = 4       // Player shoots
    };

    /**
     * @brief Struct that holds data related to a sprite
     * 
     * This struct is used to store the type of sprite (see above), the ID of the sprite,
     * the position X and the position Y. This struct is used to send the data from the server to the client.
     */
    struct SpritePositions {
        SpritesTypes entityType;        // The type of sprite
        int spriteID;                   // The ID of the sprite
        float poxX;                     // The position X
        float poxY;                     // The position Y
    };

    /**
     * @brief Struct that holds data related to a killed sprite
     * 
     * This struct is used to store the ID of the sprite and the type of the sprite.
     * This struct is used to send the data from the server to the client.
     */
    struct KilledSprite {
        int spriteID;                   // The ID of the sprite
        SpritesTypes entityType;        // The type of sprite
    };

    /**
     * @brief Struct that holds data related to an user input
     * 
     * This struct is used to store the client ID of the client sending the input,
     * the action done by the user (see above).
     * This struct is used to send the data from the client to the server.
     */
    struct Input {
        int clientID;
        InputActions action;
    };

};