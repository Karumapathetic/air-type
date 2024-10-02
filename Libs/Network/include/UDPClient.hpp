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
            UDPClient(std::string host, std::string port);
            ~UDPClient();

            void run();
            void send();
            void receive();

            void add_send_queue(std::string new_message);
            void pop_recv_queue();
            std::queue<std::string> get_recv_queue();

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::resolver::results_type _endpoints;
            asio::ip::udp::endpoint _sender_endpoint;
            std::array<char, 1024> _recv_buf;
            std::queue<std::string> _recv_queue;
            std::queue<std::string> _send_queue;
    };
}
