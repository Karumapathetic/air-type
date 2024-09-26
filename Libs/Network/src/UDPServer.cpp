/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace Network {
    UDPServer::UDPServer(int port) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {
        _isRunning = true;
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::run() {
        try {
            while (_isRunning) {
                std::string client_message = receive();
                if (!client_message.empty()) {
                    send("Hello client, I'm server");
                }
            }
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    void UDPServer::send(std::string message) {
        std::error_code ignored_error;
        asio::ip::udp::endpoint remote_endpoint;
        _socket.send_to(asio::buffer(message), remote_endpoint, 0, ignored_error);
    }

    std::string UDPServer::receive() {
        std::string recv_buf;
        asio::ip::udp::endpoint remote_endpoint;
        _socket.receive_from(asio::buffer(recv_buf), remote_endpoint);

        std::cout << "Client message -> " << recv_buf << std::endl;
        return recv_buf;
    }
}
