/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#pragma once

#include <iostream>
#include <asio.hpp>
#include <queue>

namespace Network {
    class UDPClient {
        public:
            UDPClient(std::string host, int port);
            ~UDPClient();

            void send_data(const std::string& data);
            void receive_data(bool *stop);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            std::string _address;
            int _port;
    };
}
