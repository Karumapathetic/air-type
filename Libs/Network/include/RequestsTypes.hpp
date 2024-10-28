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
        AcknowledgeRequest
    };

    // Add structures for types of requests

};