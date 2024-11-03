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

    /**
     * @brief The interface class for the Client
     * 
     * @tparam T The type of the Requests
     */
    template <typename T>
    class IClient
    {
        public:
            /**
             * @brief Construct a new IClient object
             * 
             * The constructor of the IClient class
             */
            IClient() {}

            /**
             * @brief Destroy the IClient object
             * 
             * The destructor of the IClient class
             */
            virtual ~IClient() {}

            /**
             * @brief Connect to the server
             * 
             * @param host IP address of the client
             * @param port Port of the client
             * @return true If connection succeed
             * @return false If connection failed
             */
            virtual bool connect(const std::string &host, const uint16_t port) = 0;

            /**
             * @brief Disconnect from the server
             * 
             */
            virtual void disconnect() = 0;

            /**
             * @brief Check if the connection if still valid
             * 
             * @return true If the client is connected to the server
             * @return false If the client is not connected to the server
             */
            virtual bool isConnected() = 0;

            /**
             * @brief Send a request to the server
             * 
             * @param request Request to be sent
             */
            virtual void sendRequest(const Network::Request<T> &request) = 0;

            /**
             * @brief Get the Incoming Requests object
             * 
             * @return Network::ThreadSafeQueue<Network::OwnedRequest<T>>& The queue of incoming request
             */
            virtual Network::ThreadSafeQueue<Network::OwnedRequest<T>> &getIncomingRequests() = 0;
    };

};