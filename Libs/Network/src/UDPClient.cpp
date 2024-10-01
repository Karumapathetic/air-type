/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

namespace Network {
    UDPClient::UDPClient(std::string host, std::string port)
        : _socket(_io_context, asio::ip::udp::v4()) {
            asio::ip::udp::resolver resolver(_io_context);
            _endpoints = resolver.resolve(asio::ip::udp::v4(), host, port);
            send("Hello server");
        }

    UDPClient::~UDPClient() {
    }

    void UDPClient::receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _sender_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    std::cout << "Received: " << std::string(_recv_buf.data(), bytes_recvd) << std::endl;
                } else if (ec) {
                    std::cerr << "Receive error: " << ec.message() << std::endl;
                }
            }
        );
    }

    void UDPClient::send(std::string message) {
        std::string message1 = "Hello server";
        _socket.async_send_to(
            asio::buffer(message1), *_endpoints.begin(),
            [this](std::error_code ec, std::size_t bytes) {
                if (!ec) {
                    receive();
                } else {
                    std::cerr << "Send error: " << ec.message() << std::endl;
                }
            }
        );
    }

    void UDPClient::run() {
        _io_context.run();
    }
}
