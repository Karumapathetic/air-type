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

    /**
     * @brief The interface class for the Server
     * 
     * @tparam T The type of the Requests
     */
    template <typename T>
    class IServer
    {
        public:
            /**
             * @brief Construct a new IServer object
             * 
             * The constructor of the IServer class
             */
            IServer() {}

            /**
             * @brief Destroy the IServer object
             * 
             * The destructor of the IServer class
             */
            virtual ~IServer() {}

            /**
             * @brief Start the server
             * 
             * @return true If server successfully launched
             * @return false If something stops the launching
             */
            virtual bool start() = 0;

            /**
             * @brief Stop the server
             * 
             */
            virtual void stop() = 0;

            /**
             * @brief Update the server
             * 
             */
            virtual void update() = 0;

            /**
             * @brief Send a request to a specific client
             * 
             * @param request The request to be sent
             * @param client The client supposed to get the request
             */
            virtual void sendRequestToClient(const Network::Request<T> &request, std::shared_ptr<Network::UDPConnection<T>> client) = 0;

            /**
             * @brief Send a request to all the clients
             * 
             * @param request The request to be sent
             * @param clientToIgnore The client to ignore is there is one
             */
            virtual void sendRequestToAllClients(const Network::Request<T> &request, std::shared_ptr<Network::UDPConnection<T>> clientToIgnore = nullptr) = 0;

        protected:
            /**
             * @brief Handle a request when one is received
             * 
             * @param client Client that sent the request
             * @param request Request sent
             */
            virtual void onRequestReceived(std::shared_ptr<UDPConnection<T>> client, Network::Request<T> &request) = 0;

            /**
             * @brief Handle a Client connection
             * 
             * @param client Client trying to connect
             * @return true If the connection works
             * @return false If the connection doesn't work
             */
            virtual bool onClientConnection(std::shared_ptr<Network::UDPConnection<T>> client) = 0;

            /**
             * @brief Handle a Client disconnection
             * 
             * @param client Client trying to disconnect
             */
            virtual void onClientDisconnection(std::shared_ptr<Network::UDPConnection<T>> client) = 0;
    };

};