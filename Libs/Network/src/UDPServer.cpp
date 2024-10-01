/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace Network {
    UDPServer::UDPServer(int port) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {
        receive();
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    std::cout << "Received: " << std::string(_recv_buf.data(), bytes_recvd) << std::endl;
                    send("Hello client");
                } else {
                    receive();
                }
        });
    }

    void UDPServer::send(std::string message) {
        _socket.async_send_to(
            asio::buffer(message), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                receive();
        });
    }

    void UDPServer::run() {
        _io_context.run();
    }
}
