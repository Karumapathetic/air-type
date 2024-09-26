/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace Network {
    UDPServer::UDPServer(int port) {
        _isRunning = true;
        _socket = asio::ip::udp::socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::run() {
        try {
            while (_isRunning) {
            }
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    void UDPServer::send() {
    }

    void UDPServer::receive() {
    }
}

    // try {
    //     asio::io_context io_context;

    //     udp::socket socket(io_context, udp::endpoint(udp::v4(), 8080));
    //     for (;;) {
    //         std::array<char, 1> recv_buf;
    //         udp::endpoint remote_endpoint;
    //         socket.receive_from(asio::buffer(recv_buf), remote_endpoint);

    //         std::string message = "Hello client, I'm server";

    //         std::error_code ignored_error;
    //         socket.send_to(asio::buffer(message), remote_endpoint, 0, ignored_error);
    //     }
    // } catch (std::exception& e) {
    //     std::cerr << e.what() << std::endl;
    //     return 1;
    // }
    // return 0;