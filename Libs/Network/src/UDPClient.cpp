/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

namespace Network {
    UDPClient::UDPClient(std::string host, int port) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), _port)) {
        _address = host;
        _port = port;
    }

    UDPClient::~UDPClient() {
    }

    void UDPClient::receive_data(bool *stop) {
        asio::ip::udp::socket socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), _port));
        while (!(*stop)) {
            std::string recv_buf(1024, '\0');
            asio::ip::udp::endpoint sender_endpoint;
            size_t len = socket.receive_from(asio::buffer(recv_buf.data(), 1024), sender_endpoint);
            std::cout << "Received: \"" << recv_buf << "\"" << std::endl;
        }
    }

    void UDPClient::send_data(const std::string& data) {
        asio::ip::udp::resolver resolver(_io_context);
        asio::ip::udp::resolver::results_type endpoints = resolver.resolve(asio::ip::udp::v4(), _address, std::to_string(8080));

        _socket.send_to(asio::buffer(data.data(), data.length()), *endpoints.begin());
    }
}
