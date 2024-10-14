/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#pragma once

#include <iostream>
#include <asio.hpp>

#include "SafeQueue.hpp"

namespace Network {
    typedef struct Client_s {
        std::string s_address;
        std::string s_port;
        int s_id;
    } Client_t;

    class UDPServer {
        public:
            UDPServer(std::string address, int port);
            ~UDPServer();

            void send_data(const std::string& data, std::string host, std::string port);
            void receive_data(bool *stop);
            void stop();

            SafeQueue<std::string>& getQueue(void);

        private:
            SafeQueue<std::string> _recv_queue;

            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::resolver _resolver;
            std::string _address;
            int _port;
    };
}
