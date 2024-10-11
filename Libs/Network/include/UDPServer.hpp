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
#include <vector>

namespace Network {
    typedef struct Client_s {
        asio::ip::udp::endpoint s_endpoint;
        std::string s_address;
        std::string s_port;
    } Client_t;

    class UDPServer {
        public:
            UDPServer(std::string address, int port);
            ~UDPServer();

            void send_data(const std::string& data, std::string host, std::string port);
            void send_all_data(const std::string& data);
            void receive_data(bool *stop);

        private:
            asio::io_context _io_context;
            asio::ip::udp::socket _socket;
            asio::ip::udp::endpoint _endpoint;
            asio::ip::udp::resolver _resolver;
            std::string _address;
            std::vector<Client_t> _clients;
            int _port;
    };
}
