/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** OwnedRequest
*/

#pragma once

#include <memory>
#include "Requests.hpp"

namespace Network {

    template <typename T> class UDPConnection;
    template <typename T> struct OwnedRequest
    {

        std::shared_ptr<UDPConnection<T>> remoteConnection = nullptr;
        Network::Request<T> request;

        friend std::ostream &operator<<(std::ostream &os, const OwnedRequest<T> &request)
        {
            os << request.request;
            return os;
        }

    };

};