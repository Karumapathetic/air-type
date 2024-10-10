/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPServer
*/

#include <thread>

#include "UDPServer.hpp"

namespace Network {
    UDPServer::UDPServer(std::string address, int port) : _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)), _resolver(_io_context) {
        _address = address;
        _port = port;
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::receive_data(bool *stop) {
        while (!(*stop)) {
            std::string recv_buf(1024, '\0');
            asio::ip::udp::endpoint sender_endpoint;
            size_t len = _socket.receive_from(asio::buffer(recv_buf.data(), 1024), sender_endpoint);
            bool isRegistered = false;
            for (auto client : _clients) {
                if (client.s_endpoint.address() == sender_endpoint.address()
                    && client.s_endpoint.port() == sender_endpoint.port())
                        isRegistered = true;
            }
            if (!isRegistered) {
                Client_t newClient;
                std::string recv_data = recv_buf;
                newClient.s_address = recv_data.substr(0, recv_data.find(':', 0));
                newClient.s_port = recv_data.substr(newClient.s_address.length() + 1, recv_data.length() - newClient.s_address.length() - 1);
                newClient.s_endpoint = sender_endpoint;
                _clients.push_back(newClient);
            }
            std::cout << "Received: \"" << recv_buf << "\" from : \"" << sender_endpoint.address() << ":" << sender_endpoint.port() << "\"" << std::endl;
        }
    }

    void UDPServer::send_data(const std::string& data, std::string host, std::string port) {
        asio::ip::udp::resolver::results_type endpoint = _resolver.resolve(asio::ip::udp::v4(), host, port);
        asio::ip::udp::socket socket(_io_context);
        socket.open(asio::ip::udp::v4());
        socket.send_to(asio::buffer(data.data(), data.length()), *endpoint.begin());
    }

    void UDPServer::send_all_data(const std::string& data) {
        for (auto client : _clients) {
            asio::ip::udp::resolver::results_type endpoint = _resolver.resolve(asio::ip::udp::v4(), client.s_address, client.s_port);
            asio::ip::udp::socket socket(_io_context);
            socket.open(asio::ip::udp::v4());
            socket.send_to(asio::buffer(data.data(), data.length()), *endpoint.begin());
        }
    }
}
