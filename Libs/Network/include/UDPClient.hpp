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
            UDPClient(std::string address);
            ~UDPClient();

            void send_data_to(const std::string& data, std::string host, std::string port);
            void send_data(const std::string& data);
            void receive_data(bool *stop);
            void stop();

        private:
            std::vector<std::string> split(std::string s, std::string delimiter);

            asio::io_context _io_context;
            asio::ip::udp::socket _socketSend;
            asio::ip::udp::socket _socketRecv;
            asio::ip::udp::resolver _resolver;
            std::string _addressSend;
            int _portSend;
            std::string _addressRecv;
            int _portRecv;
    };
}
