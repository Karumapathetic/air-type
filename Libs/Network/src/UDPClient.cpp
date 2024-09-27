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
        start_receive();
    }

    UDPClient::~UDPClient() {
    }

    void UDPClient::run() {
        try {
            _io_context.run();
            send("Hello server, I'm client");
        } catch (std::exception &err) {
            std::cerr << err.what() << std::endl;
        }
    }

    // std::string UDPClient::receive() {
    //     std::string recv_buf;
    //     asio::ip::udp::endpoint sender_endpoint;
    //     _socket.receive_from(asio::buffer(recv_buf), sender_endpoint);

    //     std::cout << "Server message -> " << recv_buf << std::endl;
    //     return recv_buf;
    // }

    void UDPClient::send(std::string message) {
        _socket.async_send_to(
            asio::buffer(message), _endpoint,
            [this](std::error_code ec, std::size_t bytes_sent) {
                if (!ec) {
                    std::cout << "Message sent : " << bytes_sent << "bytes" << std::endl;
                } else {
                    std::cerr << "Send failed: " << ec.message() << std::endl;
                }
            }
        );
    }

    void UDPClient::start_receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _sender_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec) {
                    std::cout << "Received: " << std::string(_recv_buf.data(), bytes_recvd) << std::endl;
                    start_receive();
                } else {
                    std::cerr << "Receive failed: " << ec.message() << std::endl;
                }
            }
        );
    }
}
