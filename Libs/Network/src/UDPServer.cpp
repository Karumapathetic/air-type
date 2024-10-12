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
        while (*stop) {
            std::string recv_buf(1024, '\0');
            asio::ip::udp::endpoint sender_endpoint;
            _socket.receive_from(asio::buffer(recv_buf.data(), 1024), sender_endpoint);
            std::cout << "Received: \"" << recv_buf << "\" from : \"" << sender_endpoint.address() << ":" << sender_endpoint.port() << "\"" << std::endl;
            bool isRegistered = false;
            if (recv_buf.empty())
                continue;
            for (auto client : _clients) {
                if (client.s_endpoint.address() == sender_endpoint.address()
                    && client.s_endpoint.port() == sender_endpoint.port())
                        isRegistered = true;
            }
            if (!isRegistered) {
                std::vector<std::string> parsedBuf = split(recv_buf, " ");
                if (parsedBuf[0] == "stop") {
                    std::cout << "STOP" << std::endl;
                    break;
                }
                if (parsedBuf[0] == "connect") {
                    Client_t newClient;
                    newClient.s_address = parsedBuf[1];
                    newClient.s_port = parsedBuf[2];
                    newClient.s_endpoint = sender_endpoint;
                    _clients.push_back(newClient);
                }
            }
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

    void UDPServer::stop()
    {
        this->send_data("stop", _address, std::to_string(_port));
        _socket.close();
        _io_context.stop();
    }

    std::vector<std::string> UDPServer::split(std::string s, std::string delimiter)
    {
        size_t pos_start = 0;
        size_t pos_end = 0;
        size_t delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }
        res.push_back(s.substr(pos_start));
        return res;
    }
}
