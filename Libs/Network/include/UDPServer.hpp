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
            void send();
            void receive();

        private:
            bool _isRunning;
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            // asio::ip::udp::endpoint _endpoint;
    };
}