/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** RequestsTypes
*/

#pragma once

#include <cstdint>

namespace Network {

    enum class RequestsTypes : uint32_t
    {
        ClientConnection,
        ServerPing,
        ServerRequest,
        ServerAcceptance,
        ServerDenial,
        AcknowledgeRequest,
        SetSpritePosition,
        NotifyKilledSprite,
        SetInput,
        LaunchGame
    };

    enum class SpritesTypes : uint32_t
    {
        Player,
        Enemy,
        Missile
    };

    enum class InputActions : uint32_t
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SHOOT
    };

    struct SpritePositions {
        SpritesTypes entityType;
        int spriteID;
        float poxX;
        float poxY;
    };

    struct KilledSprite {
        int spriteID;
        float posX;
        float posY;
    };

    struct Input {
        int clientID;
        InputActions action;
    };

};