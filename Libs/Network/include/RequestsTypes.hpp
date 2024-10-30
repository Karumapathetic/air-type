/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** RequestsTypes
*/

#pragma once

#include <cstdint>

namespace Network {

    /// @brief Enum that define every types of requests
    /// @enum RequestsTypes
    enum class RequestsTypes : uint32_t
    {
        ClientConnection,       // The Client try to connect
        ServerPing,             // The Client ping the server
        ServerAcceptance,       // The Server accept Client connection
        ServerDenial,           // The Server refuse Client connection
        AcknowledgeRequest,     // The Server or Client acknowledge previous request
        SetSpritePosition,      // The Server send a sprite positions
        NotifyKilledSprite,     // The Server notify a entity is killed
        SetInput,               // The Client send user input to Server
        LaunchGame              // The Server launch the game
    };

    /// @brief Enum that define every types of sprites
    /// @enum SpritesTypes
    enum class SpritesTypes : uint32_t
    {
        Player,         // Player type
        PataPata,       // Pata-Pata type
        Win,            // Win type
        Wick,           // Wick type
        Geld,           // Geld type
        Bug,            // Bug type
        Missile         // Missile type
    };

    /// @brief Enum that define every types of actions
    /// @enum InputActions
    enum class InputActions : uint32_t
    {
        UP,         // Player goes up
        DOWN,       // Player goes down
        LEFT,       // Player goes left
        RIGHT,      // Player goes right
        SHOOT       // Player shoots
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
     * This struct is used to store the ID of the sprite, the position X and the position Y.
     * This struct is used to send the data from the server to the client.
     */
    struct KilledSprite {
        int spriteID;                   // The ID of the sprite
        float posX;                     // The position X
        float posY;                     // The position Y
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