/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPConnection
*/

#pragma once

#include <iostream>
#include <asio.hpp>

#include "ThreadSafeQueue.hpp"
#include "OwnedRequest.hpp"
#include "Requests.hpp"
#include "RequestsTypes.hpp"

namespace Network
{

    /**
     * @brief Define the IServer class
     * 
     * @tparam T Type of requests
     */
    template <typename T> class IServer;

    /**
     * @brief Class used for UDP connections
     * 
     * @tparam T Type of requests
     */
    template <typename T>
    class UDPConnection : public std::enable_shared_from_this<UDPConnection<T>>
    {
        public:
            /**
             * @brief Enum to separate behavior on client and server
             * 
             */
            enum class actualOwner
            {
                CLIENT,
                SERVER
            };

            /**
             * @brief Construct a new UDPConnection object
             * 
             * @param owner Define if connection is for server or client
             * @param otherContext Get the context of the owner
             * @param socket Get the socket of the owner
             * @param otherEndpoint Get the endpoint of the owner
             * @param incomingRequests Get the queue of received requests of the owner
             */
            UDPConnection(
                actualOwner owner,
                asio::io_context &otherContext,
                asio::ip::udp::socket socket,
                asio::ip::udp::endpoint otherEndpoint,
                Network::ThreadSafeQueue<Network::OwnedRequest<T>> &incomingRequests
            ) :
                _socket(std::move(socket)),
                _endpoint(std::move(otherEndpoint)),
                _context(otherContext),
                _incomingQueue(incomingRequests)
            {
                ownerType = owner;
            }

            /**
             * @brief Destroy the UDPConnection object
             * 
             */
            virtual ~UDPConnection() {};

            /**
             * @brief Get the Id object
             * 
             * @return uint32_t ID of the connection
             */
            uint32_t getId() const
            {
                return _id;
            }

            /**
             * @brief Get the Endpoint object
             * 
             * @return const asio::ip::udp::endpoint& Endpoint of the connection
             */
            const asio::ip::udp::endpoint &getEndpoint() const
            {
                return _endpoint;
            }

            /**
             * @brief Get the Socket object
             * 
             * @return const asio::ip::udp::socket& Socket of the connection
             */
            const asio::ip::udp::socket &getSocket() const
            {
                return _socket;
            }

            /**
             * @brief Make the server connection to the client
             * 
             * @param server Server handling connection
             * @param clientId Client ID
             */
            void makeClientConnection(Network::IServer<T> *server, uint32_t clientId = 0)
            {
                if (ownerType == actualOwner::SERVER) {
                    if (_socket.is_open()) {
                        _id = clientId;
                        readHeader();
                    } else {
                        std::cerr << "Socket is not open" << std::endl;
                    }
                }
            }

            /**
             * @brief Make the client connection to the server
             * 
             */
            void makeServerConnection()
            {
                if (ownerType == actualOwner::CLIENT) {
                    readHeader();
                    Network::Request<RequestsTypes> request;
                    request.header.id = RequestsTypes::ClientConnection;
                    sendRequest(request);
                }
            }

            /**
             * @brief Check of the connection is available
             * 
             * @return true If the connection is available
             * @return false If the connection is not available
             */
            bool isConnected() const
            {
                return _socket.is_open();
            }

            /**
             * @brief Disconnect the owner
             * 
             */
            void disconnect()
            {
                if (isConnected())
                    asio::post(_context, [this]() { _socket.close(); });
            }

            /**
             * @brief Send a request to the remote endpoint
             * 
             * @param request Request to be sent
             */
            void sendRequest(const Network::Request<T> &request)
            {
                asio::post(_context, [this, request]() {
                    bool writingRequest = _outgoingQueue.isEmpty();
                    _outgoingQueue.pushBack(request);
                    if (writingRequest)
                        writeHeader();
                });
            }

        protected:
            /**
             * @brief Socket of the connection (asio related)
             * 
             */
            asio::ip::udp::socket _socket;

            /**
             * @brief Endpoint of the connection (asio related)
             * 
             */
            asio::ip::udp::endpoint _endpoint;

            /**
             * @brief Context of the connection (asio related)
             * 
             */
            asio::io_context &_context;

            /**
             * @brief ID of the connection
             * 
             */
            uint32_t _id = 0;

            /**
             * @brief Owner of the connection
             * 
             */
            actualOwner ownerType;

            /**
             * @brief Queue of received requests
             * 
             */
            Network::ThreadSafeQueue<Network::OwnedRequest<T>> &_incomingQueue;

            /**
             * @brief Queue of requests to send
             * 
             */
            Network::ThreadSafeQueue<Network::Request<T>> _outgoingQueue;

            /**
             * @brief Temporary request to store
             * 
             */
            Network::Request<T> _tmpRequest;

        private:
            /**
             * @brief Send the header of front request in the queue to the remote endpoint
             * 
             */
            void writeHeader()
            {
                _socket.async_send_to(asio::buffer(&_outgoingQueue.front().header, sizeof(Network::RequestHeader<T>)),
                _endpoint, [this](std::error_code ec, std::size_t bytesWrote)
                {
                    if (!ec) {
                        if (_outgoingQueue.front().body.size() > 0) {
                            writeBody();
                        } else {
                            _outgoingQueue.popFront();
                            if (!_outgoingQueue.isEmpty())
                                writeHeader();
                        }
                    } else {
                        std::cerr << _id << ": write header failed " << ec << std::endl;
                        _socket.close();
                    }
                });
            }

            /**
             * @brief Send the body of front request in the queue to the remote endpoint
             * 
             */
            void writeBody()
            {
                _socket.async_send_to(asio::buffer(_outgoingQueue.front().body.data(), _outgoingQueue.front().body.size()),
                _endpoint, [this](std::error_code ec, std::size_t bytesWrote) {
                    if (!ec) {
                        _outgoingQueue.popFront();
                        if (!_outgoingQueue.isEmpty())
                            writeHeader();
                    } else {
                        std::cerr << _id << ": write body failed " << ec << std::endl;
                        _socket.close();
                    }
                });
            }

            /**
             * @brief Add a request to the queue of requests to send
             * 
             */
            void addRequestToIncomingQueue()
            {
                if (ownerType == actualOwner::SERVER) {
                    _incomingQueue.pushBack({this->shared_from_this(), _tmpRequest});
                } else {
                    _incomingQueue.pushBack({nullptr, _tmpRequest});
                }
                readHeader();
            }

            /**
             * @brief Read the header of a received request
             * 
             */
            void readHeader()
            {
                _socket.async_receive_from(asio::buffer(&_tmpRequest.header, sizeof(Network::RequestHeader<T>)),
                _endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
                    if (!ec) {
                        if (_tmpRequest.header.size > 0) {
                            _tmpRequest.body.resize(_tmpRequest.header.size);
                            readBody();
                        } else {
                            addRequestToIncomingQueue();
                        }
                    } else {
                        std::cerr << _id << ": read header failed " << ec << std::endl;
                        _socket.close();
                    }
                });
            }

            /**
             * @brief Read the body of a received request
             * 
             */
            void readBody()
            {
                _socket.async_receive_from(asio::buffer(_tmpRequest.body.data(), _tmpRequest.header.size),
                _endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
                    if (!ec) {
                        addRequestToIncomingQueue();
                    } else {
                        std::cerr << _id << ": read body failed " << ec << std::endl;
                        _socket.close();
                    }
                });
            }
    };

};