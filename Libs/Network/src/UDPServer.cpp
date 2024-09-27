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
        start_receive();
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::run() {
        try {
            _io_context.run();
        } catch (std::exception& err) {
            std::cerr << err.what() << std::endl;
        }
    }

    void UDPServer::send(const std::string& message, const asio::ip::udp::endpoint& remote_endpoint) {
        _socket.async_send_to(
            asio::buffer(message), remote_endpoint,
            [this](std::error_code ec, std::size_t bytes_sent) {
                if (!ec) {
                    std::cout << "Message sent: " << bytes_sent << " bytes" << std::endl;
                } else {
                    std::cerr << "Send failed: " << ec.message() << std::endl;
                }
            }
        );
    }

    // std::string UDPServer::receive(asio::ip::udp::endpoint& remote_endpoint) {
    //     std::array<char, 1024> recv_buf;
    //     std::error_code error;
    //     size_t len = _socket.receive_from(asio::buffer(recv_buf), remote_endpoint, 0, error);

    //     if (error && error != asio::error::message_size) {
    //         std::cerr << "Receive failed: " << error.message() << std::endl;
    //         return "";
    //     }

    //     std::string result(recv_buf.data(), len);
    //     std::cout << "Client message -> " << result << std::endl;
    //     return result;
    // }

    void UDPServer::start_receive() {
        _socket.async_receive_from(
            asio::buffer(_recv_buf), _remote_endpoint,
            std::bind(&UDPServer::handle_receive, this,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
    }

    void UDPServer::handle_receive(const std::error_code& error, std::size_t bytes_send) {
        if (!error) {
            std::shared_ptr<std::string> message(new std::string("test"));
            _socket.async_send_to(asio::buffer(*message), _remote_endpoint,
            std::bind(&UDPServer::handle_send, this, message,
            asio::placeholders::error,
            asio::placeholders::bytes_transferred));
            start_receive();
        }
    }

    void UDPServer::handle_send(std::shared_ptr<std::string> message, const std::error_code& error, std::size_t bytes_sent) {
        if (error) {
            std::cerr << error.message() << std::endl;
        }
    }
}
