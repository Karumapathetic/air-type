/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#pragma once

#include <iostream>
#include <asio.hpp>

namespace Network {
    class UDPServer {
        public:
            UDPServer(int port);
            ~UDPServer();

            void run();
            void send(const std::string& message, const asio::ip::udp::endpoint& remote_endpoint);
            void start_receive();
            void handle_receive(const std::error_code &error, std::size_t bytes_send);
            void handle_send(std::shared_ptr<std::string> message, const std::error_code& error, std::size_t bytes_sent);

        private:
            bool _isRunning;
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _remote_endpoint;
            std::array<char, 1024> _recv_buf;
    };
}