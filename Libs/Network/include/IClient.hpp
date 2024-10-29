/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IClient
*/

#pragma once

#include <iostream>
#include <cstdint>

#include "Requests.hpp"
#include "ThreadSafeQueue.hpp"
#include "OwnedRequest.hpp"

namespace Network
{

    template <typename T>
    class IClient
    {
        public:
            IClient() {}
            virtual ~IClient() {}

            virtual bool connect(const std::string &host, const uint16_t port) = 0;
            virtual void disconnect() = 0;
            virtual bool isConnected() = 0;

            virtual void sendRequest(const Network::Request<T> &request) = 0;
            virtual Network::ThreadSafeQueue<Network::OwnedRequest<T>> &getIncomingRequests() = 0;
    };

};