/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IServer
*/

#pragma once

#include "UDPConnection.hpp"
#include "Requests.hpp"

namespace Network
{

    template <typename T>
    class IServer
    {
        public:
            IServer() {}
            virtual ~IServer() {}

            virtual bool start() = 0;
            virtual void stop() = 0;
            virtual void waitForRequest() = 0;

            virtual void sendRequestToClient(const Network::Request<T> &request, std::shared_ptr<Network::UDPConnection<T>> client) = 0;
            virtual void sendRequestToAllClients(const Network::Request<T> &request, std::shared_ptr<Network::UDPConnection<T>> clientToIgnore = nullptr) = 0;

        protected:
            virtual void onRequestReceived(std::shared_ptr<UDPConnection<T>> client, Network::Request<T> &request) = 0;
            virtual bool onClientConnection(std::shared_ptr<Network::UDPConnection<T>> client) = 0;
            virtual void onClientDisconnection(std::shared_ptr<Network::UDPConnection<T>> client) = 0;
    };

};