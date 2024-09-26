/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

namespace Network {
    UDPClient::UDPClient(std::string host, std::string port) : _socket(_io_context), _resolver(_io_context) {
        _endpoint = *_resolver.resolve(asio::ip::udp::v4(), host, port).begin();
        _socket.open(asio::ip::udp::v4());
    }

    UDPClient::~UDPClient() {
    }

    void UDPClient::run() {

    }

    std::string UDPClient::receive() {
        std::string recv_buf;
        asio::ip::udp::endpoint sender_endpoint;
        _socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

        std::cout << "Server message -> " << recv_buf << std::endl;
        return recv_buf;
    }

    void UDPClient::send(std::string message) {
        _socket.send_to(asio::buffer(message), _endpoint);
    }
}
