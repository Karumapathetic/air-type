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

    template <typename T> class IServer;

    template <typename T>
    class UDPConnection : public std::enable_shared_from_this<UDPConnection<T>>
    {
        public:
            enum class actualOwner
            {
                CLIENT,
                SERVER
            };

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

            virtual ~UDPConnection() {};

            uint32_t getId() const
            {
                return _id;
            }

            const asio::ip::udp::endpoint &getEndpoint() const
            {
                return _endpoint;
            }

            const asio::ip::udp::socket &getSocket() const
            {
                return _socket;
            }

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

            void makeServerConnection()
            {
                if (ownerType == actualOwner::CLIENT) {
                    readHeader();
                    Network::Request<RequestsTypes> request;
                    request.header.id = RequestsTypes::ClientConnection;
                    sendRequest(request);
                }
            }

            bool isConnected() const
            {
                return _socket.is_open();
            }

            void disconnect()
            {
                if (isConnected())
                    asio::post(_context, [this]() { _socket.close(); });
            }

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
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::io_context &_context;

            uint32_t _id = 0;
            actualOwner ownerType;
            Network::ThreadSafeQueue<Network::OwnedRequest<T>> &_incomingQueue;
            Network::ThreadSafeQueue<Network::Request<T>> _outgoingQueue;
            Network::Request<T> _tmpRequest;

        private:
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

            void addRequestToIncomingQueue()
            {
                if (ownerType == actualOwner::SERVER) {
                    _incomingQueue.pushBack({this->shared_from_this(), _tmpRequest});
                } else {
                    _incomingQueue.pushBack({nullptr, _tmpRequest});
                }
                readHeader();
            }

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