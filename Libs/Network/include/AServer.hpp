/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** AServer
*/

#pragma once

#include "IServer.hpp"
#include "RequestsTypes.hpp"

namespace Network
{

    template <typename T>
    class AServer : virtual public Network::IServer<RequestsTypes>
    {
        public:
            AServer() : Network::IServer<RequestsTypes>(), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 60000))
            {
                start();
            }

            ~AServer()
            {
                stop();
            }

            bool start()
            {
                try {
                    waitForRequest();

                    _contextThread = std::thread([this]() { _context.run(); });
                } catch (std::exception &e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                    return false;
                }
                std::cout << "Server started!" << std::endl;
                return true;
            }

            void update() {}

            void stop()
            {
                _context.stop();
                if (_contextThread.joinable())
                    _contextThread.join();
                std::cout << "Server stopped!" << std::endl;
            }

            void waitForRequest()
            {
                _socket.async_receive_from(asio::buffer(_tmpBuffer.data(), _tmpBuffer.size()),
                _clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived) {
                    if (_clientEndpoint.protocol() != asio::ip::udp::v4())
                        return waitForRequest();
                    if (!ec) {
                        for (std::shared_ptr<UDPConnection<T>> &connection : _connectionsQueue) {
                            if (connection->getEndpoint() == _clientEndpoint) {
                                return;
                            }
                        }
                        asio::ip::udp::socket newSocket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
                        std::shared_ptr<UDPConnection<T>> newConnection = std::make_shared<UDPConnection<T>>(UDPConnection<T>::actualOwner::SERVER, _context, std::move(newSocket), _clientEndpoint, _incomingRequests);
                        if (onClientConnection(newConnection)) {
                            _connectionsQueue.push_back(std::move(newConnection));
                            _connectionsQueue.back()->makeClientConnection(this, _id++);
                        } else {
                            std::cerr << "Connection denied" << std::endl;
                        }
                    } else {
                        std::cerr << "Error on connection : " << ec.message() << std::endl;
                    }
                    waitForRequest();
                });
            }

            void sendRequestToClient(const Request<T> &request, std::shared_ptr<UDPConnection<T>> client)
            {
                if (client && client->isConnected()) {
                    std::cout << "Sending to client" << std::endl;
                    client->sendRequest(request);
                    std::cout << "Finished sending to client" << std::endl;
                } else {
                    onClientDisconnection(client);
                    client.reset();
                    _connectionsQueue.erase(std::remove(_connectionsQueue.begin(), _connectionsQueue.end(), client), _connectionsQueue.end());
                }
            }

            void sendRequestToAllClients(const Network::Request<T> &request, std::shared_ptr<Network::UDPConnection<T>> clientToIgnore = nullptr)
            {
                bool invalidClientExists = false;

                for (auto &client : _connectionsQueue) {
                    if (client && client->isConnected()) {
                        if (client != clientToIgnore)
                            client->sendRequest(request);
                    } else {
                        onClientDisconnection(client);
                        client.reset();
                        invalidClientExists = true;
                    }
                }
                if (invalidClientExists)
                    _connectionsQueue.erase(std::remove(_connectionsQueue.begin(), _connectionsQueue.end(), nullptr), _connectionsQueue.end());
            }

        protected:
            Network::ThreadSafeQueue<Network::OwnedRequest<T>> _incomingRequests;
            std::deque<std::shared_ptr<UDPConnection<T>>> _connectionsQueue;

            asio::io_context _context;
            std::thread _contextThread;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _clientEndpoint;

            std::array<char, 1024> _tmpBuffer;
            uint32_t _id = 0;

            void onRequestReceived(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client, Network::Request<RequestsTypes> &request)
            {
                std::cout << "Message received from client : " << client->getId() << std::endl;
            }

            bool onClientConnection(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client)
            {
                Network::Request<RequestsTypes> request;
                request.header.id = RequestsTypes::ServerAcceptance;
                client->sendRequest(request);
                return true;
            }

            virtual void onClientDisconnection(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client)
            {
                std::cout << "Client disconnected: " << client->getId() << std::endl;
            }
    };

};