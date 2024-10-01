/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#pragma once

#include <iostream>
#include <asio.hpp>

namespace Network {
    class UDPClient {
        public:
            UDPClient(std::string host, std::string port);
            ~UDPClient();

            void run();
            void send(std::string message);
            void receive();

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::resolver::results_type _endpoints;
            asio::ip::udp::endpoint _sender_endpoint;
            std::array<char, 1024> _recv_buf;
    };
}
