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
        }

    UDPClient::~UDPClient() {
    }

    void UDPClient::receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _sender_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    std::cout << "Received: " << std::string(_recv_buf.data(), bytes_recvd) << std::endl;
                    _recv_queue.push(std::string(_recv_buf.data(), bytes_recvd));
                    send();
                } else if (ec) {
                    receive();
                    std::cerr << "Receive error: " << ec.message() << std::endl;
                }
            }
        );
    }

    void UDPClient::send() {
        std::string message = _send_queue.front();
        if (_send_queue.size() == 0)
            std::cout << "Queue is empty" << std::endl;
        std::cout << "Sending : " << message << std::endl;
        _socket.async_send_to(
            asio::buffer(message), *_endpoints.begin(),
            [this](std::error_code ec, std::size_t bytes) {
                if (!ec)
                    _send_queue.pop();
                receive();
            }
        );
    }

    void UDPClient::run() {
        send();
        _io_context.run();
    }

    void UDPClient::add_send_queue(std::string new_message) {
        std::cout << "Adding : \"" << new_message << "\" to the queue" << std::endl;
        _send_queue.push(new_message);
    }

    std::queue<std::string> UDPClient::get_recv_queue() {
        return _recv_queue;
    }

    void UDPClient::pop_recv_queue() {
        _recv_queue.pop();
    }
}
