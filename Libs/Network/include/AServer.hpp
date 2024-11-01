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

    /**
     * @brief Abstract class of the Server
     * 
     * @tparam T Type of the requests
     */
    template <typename T>
    class AServer : virtual public Network::IServer<RequestsTypes>
    {
        public:
            /**
             * @brief Construct a new AServer object
             * 
             * Constructor of the AServer class
             * This constructor sets the socket of the server and start it
             */
            AServer() : Network::IServer<RequestsTypes>(), _socket(_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 60000))
            {
                std::cout << "Server address: " << std::flush;
                #ifdef _WIN32
                    system("powershell -Command \"(Get-NetIPAddress -AddressFamily IPv4 | Where-Object {$_.InterfaceAlias -like \"'Wi-Fi'\"}).IPAddress\"");
                #else
                    system("ip -o route get to 8.8.8.8 | sed -n 's/.*src \\([0-9.]\\+\\).*/\\1/p'");
                #endif
                std::cout << std::endl;
                start();
            }

            /**
             * @brief Destroy the AServer object
             * 
             * Destructor of the server
             * This destructor call the stop function to stop the server before being deleted
             */
            ~AServer()
            {
                stop();
            }

            /**
             * @brief Start to receive data in a separated thread
             * 
             * @return true If the server has started
             * @return false If the server hasn't started
             */
            bool start()
            {
                try {
                    waitForRequest();

                    _contextThread = std::thread([this]() { _context.run(); });
                } catch (std::exception &e) {
                    std::cerr << "Exception: " << e.what() << std::endl;
                    return false;
                }
                return true;
            }

            /**
             * @brief Update the server
             * 
             * This function is not define here because it can vary in the real Server class
             */
            void update() {}

            /**
             * @brief Stops the server
             * 
             * This function stops the context, and the thread that receive requests
             */
            void stop()
            {
                Network::Request<Network::RequestsTypes> request;
                request.header.id = Network::RequestsTypes::ClientDisconnection;
                request.header.size = 0;
                for (auto &client : _connectionsQueue)
                    client->sendRequest(request);
                usleep(500);
                _context.stop();
                if (_contextThread.joinable())
                    _contextThread.join();
            }

            /**
             * @brief Wait for new connection to register the clients
             * 
             */
            void waitForRequest()
            {
                _socket.async_receive_from(asio::buffer(_tmpBuffer.data(), _tmpBuffer.size()),
                _clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived) {
                    if (_clientEndpoint.protocol() != asio::ip::udp::v4())
                        return waitForRequest();
                    if (!ec) {
                        if (_nbClients >= 4)
                            return;
                        for (std::shared_ptr<UDPConnection<T>> &connection : _connectionsQueue) {
                            if (connection->getEndpoint() == _clientEndpoint)
                                return;
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

            /**
             * @brief Send a request to a specific client
             * 
             * @param request Request to be sent
             * @param client Client to sent the request to
             */
            void sendRequestToClient(const Request<T> &request, std::shared_ptr<UDPConnection<T>> client)
            {
                if (client && client->isConnected()) {
                    client->sendRequest(request);
                } else {
                    onClientDisconnection(client);
                    client.reset();
                    _connectionsQueue.erase(std::remove(_connectionsQueue.begin(), _connectionsQueue.end(), client), _connectionsQueue.end());
                }
            }

            /**
             * @brief Send a request to all clients
             * 
             * @param request Request to be sent
             * @param clientToIgnore Client to ignore if there is one
             */
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
            /**
             * @brief Queue of received requests
             * 
             */
            Network::ThreadSafeQueue<Network::OwnedRequest<T>> _incomingRequests;

            /**
             * @brief Queue of connected clients
             * 
             */
            std::deque<std::shared_ptr<UDPConnection<T>>> _connectionsQueue;

            /**
             * @brief Context of the server (asio related)
             * 
             */
            asio::io_context _context;

            /**
             * @brief Separated thread that run the requests reception
             * 
             */
            std::thread _contextThread;

            /**
             * @brief Socket of the server (asio related)
             * 
             */
            asio::ip::udp::socket _socket;

            /**
             * @brief Temporary client endpoint (asio related)
             * 
             * This endpoint is used to receive new connection requests
             */
            asio::ip::udp::endpoint _clientEndpoint;

            /**
             * @brief Temporary buffer
             * 
             * This buffer is used to receive new connection requests
             */
            std::array<char, 1024> _tmpBuffer;

            /**
             * @brief Store the id of the client (and the connection)
             * 
             */
            uint32_t _id = 0;

            std::array<int, 4> _clientsID = {-1, -1, -1, -1};

            int _nbClients = 0;

            /**
             * @brief Handle the request reception
             * 
             * @param client Client sending the request
             * @param request Request received
             */
            void onRequestReceived(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client, Network::Request<RequestsTypes> &request)
            {
            }

            /**
             * @brief Handle a client connection
             * 
             * @param client Client trying to connect
             * @return true If the client is connected
             * @return false If the client is not connected
             */
            bool onClientConnection(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client)
            {
                Network::Request<RequestsTypes> request;
                request.header.id = RequestsTypes::ServerAcceptance;
                client->sendRequest(request);
                return true;
            }

            /**
             * @brief Handle a client disconnection
             * 
             * @param client Client trying to disconnect
             */
            virtual void onClientDisconnection(std::shared_ptr<Network::UDPConnection<RequestsTypes>> client)
            {
                Network::Request<RequestsTypes> request;
                request.header.id = RequestsTypes::ServerAcceptance;
                client->sendRequest(request);
            }
    };
};
