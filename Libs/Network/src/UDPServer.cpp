/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace Network {
    UDPServer::UDPServer(int port) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)) {
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    std::cout << "Received: " << std::string(_recv_buf.data(), bytes_recvd) << std::endl;
                    _recv_queue.push(std::string(_recv_buf.data(), bytes_recvd));
                    send();
                } else {
                    receive();
                }
        });
    }

    void UDPServer::send() {
        std::string message = _send_queue.front();
        if (_send_queue.size() == 0)
        std::cout << "Queue is empty" << std::endl;
        std::cout << "Sending : " << message << std::endl;
        _socket.async_send_to(
            asio::buffer(message), _remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec)
                    _send_queue.pop();
                receive();
        });
    }

    void UDPServer::run() {
        receive();
        _io_context.run();
    }

    void UDPServer::add_send_queue(std::string new_message) {
        std::cout << "Adding : \"" << new_message << "\" to the queue" << std::endl;
        _send_queue.push(new_message);
    }

    std::queue<std::string> UDPServer::get_recv_queue() {
        return _recv_queue;
    }

    void UDPServer::pop_recv_queue() {
        _recv_queue.pop();
    }
}
