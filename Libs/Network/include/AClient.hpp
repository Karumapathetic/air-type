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
    template <typename T>
    class AClient : virtual public IClient<T>
    {
        public:
            AClient() {}
            virtual ~AClient() { disconnect(); }

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

            void disconnect()
            {
                if (isConnected())
                    _connection->disconnect();
                _context.stop();
                if (_contextThread.joinable())
                    _contextThread.join();
                _connection.release();
            }

            bool isConnected()
            {
                if (_connection)
                    return _connection->isConnected();
                return false;
            }

            void sendRequest(const Network::Request<T> &request)
            {
                if (isConnected())
                    _connection->sendRequest(request);
            }

            Network::ThreadSafeQueue<Network::OwnedRequest<T>> &getIncomingRequests()
            {
                return _incomingRequests;
            }

            const std::unique_ptr<UDPConnection<T>> &getConnection()
            {
                return _connection;
            }

        protected:
            asio::io_context _context;
            std::thread _contextThread;
            std::unique_ptr<Network::UDPConnection<T>> _connection;

        private:
            Network::ThreadSafeQueue<OwnedRequest<T>> _incomingRequests;
    };
};