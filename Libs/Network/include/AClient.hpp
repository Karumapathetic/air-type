/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** AClient
*/

#pragma once

#include <thread>
#include <asio.hpp>

#include "IClient.hpp"
#include "UDPConnection.hpp"

namespace Network
{
    /**
     * @brief Abstract class of the client
     * 
     * @tparam T Type of requests
     */
    template <typename T>
    class AClient : virtual public IClient<T>
    {
        public:
            /**
             * @brief Construct a new AClient object
             * 
             * Constructor of the AClient class
             */
            AClient() {}

            /**
             * @brief Destroy the AClient object
             * 
             * Destructor of the AClient class
             * Disconnect the client from the server
             */
            virtual ~AClient() { disconnect(); }

            /**
             * @brief Connect the client to the server
             * 
             * @param host IP address of the client
             * @param port Port of the client
             * @return true If the client is connected
             * @return false If the client is not connected
             */
            bool connect(const std::string &host, const uint16_t port)
            {
                try {
                    asio::ip::udp::endpoint remoteEndpoint = asio::ip::udp::endpoint(asio::ip::address::from_string(host), port);
                    asio::ip::udp::socket socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
                    _connection = std::make_unique<UDPConnection<T>>(UDPConnection<T>::actualOwner::CLIENT, _context, std::move(socket), std::move(remoteEndpoint), _incomingRequests);
                    _connection->makeServerConnection();
                    _contextThread = std::thread([this]() { _context.run(); });
                } catch (std::exception &e) {
                    std::cerr << "Client connection failed: " << e.what() << std::endl;
                    return false;
                }
                return true;
            }

            /**
             * @brief Disconnect the client from the server
             * 
             */
            void disconnect()
            {
                Network::Request<Network::RequestsTypes> request;
                request.header.id = Network::RequestsTypes::ClientDisconnection;
                request.header.size = 0;
                this->sendRequest(request);
                usleep(500);
                if (isConnected())
                    _connection->disconnect();
                _context.stop();
                if (_contextThread.joinable())
                    _contextThread.join();
                _connection.release();
            }

            /**
             * @brief Check if the client is connected to the server
             * 
             * @return true If the client is connected
             * @return false If the client is not connected
             */
            bool isConnected()
            {
                if (_connection)
                    return _connection->isConnected();
                return false;
            }

            /**
             * @brief Send a request to the server
             * 
             * @param request Request to be sent
             */
            void sendRequest(const Network::Request<T> &request)
            {
                if (isConnected())
                    _connection->sendRequest(request);
            }

            /**
             * @brief Get the Incoming Requests object
             * 
             * @return Network::ThreadSafeQueue<Network::OwnedRequest<T>>& Queue of received requests
             */
            Network::ThreadSafeQueue<Network::OwnedRequest<T>> &getIncomingRequests()
            {
                return _incomingRequests;
            }

            /**
             * @brief Get the Connection object
             * 
             * @return const std::unique_ptr<UDPConnection<T>>& The connection with the server
             */
            const std::unique_ptr<UDPConnection<T>> &getConnection()
            {
                return _connection;
            }

        protected:
            /**
             * @brief Context of the client (asio related)
             * 
             */
            asio::io_context _context;

            /**
             * @brief Thread that run the context of the client
             * 
             */
            std::thread _contextThread;

            /**
             * @brief Connection class with the server
             * 
             */
            std::unique_ptr<Network::UDPConnection<T>> _connection;

        private:
            /**
             * @brief Queue of received requests
             * 
             */
            Network::ThreadSafeQueue<OwnedRequest<T>> _incomingRequests;
    };
};