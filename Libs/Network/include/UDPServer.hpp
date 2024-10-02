/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#pragma once

#include <iostream>
#include <asio.hpp>
#include <queue>

namespace Network {
    class UDPServer {
        public:
            UDPServer(int port);
            ~UDPServer();

            void run();
            void send();
            void receive();

            std::queue<std::string> get_recv_queue();
            void pop_recv_queue();
            void add_send_queue(std::string new_message);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _remote_endpoint;
            std::array<char, 1024> _recv_buf;
            std::queue<std::string> _send_queue;
            std::queue<std::string> _recv_queue;
    };
}