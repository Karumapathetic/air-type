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
            void send(std::string message);
            void receive();

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _remote_endpoint;
            std::array<char, 1024> _recv_buf;
    };
}