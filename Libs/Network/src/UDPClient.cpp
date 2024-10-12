/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** UDPClient
*/

#include "UDPClient.hpp"


namespace Network {
    UDPClient::UDPClient(std::string address)
    : _socketSend(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
    _socketRecv(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0)),
    _resolver(_io_context)
    {
        _addressSend = address;
        _portSend = _socketSend.local_endpoint().port();

        _addressRecv = "127.0.0.1";
        _portRecv = _socketRecv.local_endpoint().port();

        this->send_data("connect " + _addressRecv + " " + std::to_string(_portRecv));
    }

    UDPClient::~UDPClient() {
    }

    void UDPClient::receive_data(bool *stop) {
        while (*stop) {
            std::string recv_buf(1024, '\0');
            asio::ip::udp::endpoint sender_endpoint;
            size_t len = _socketRecv.receive_from(asio::buffer(recv_buf.data(), 1024), sender_endpoint);
            std::vector<std::string> parsedBuf = split(recv_buf, " ");
            if (parsedBuf[0] == "stop") {
                std::cout << "STOP" << std::endl;
                break;
            } else {
                std::cout << "Received: \"" << recv_buf << "\"" << std::endl;
            }
        }
    }

    void UDPClient::send_data(const std::string& data) {
        asio::ip::udp::resolver resolver(_io_context);
        asio::ip::udp::resolver::results_type endpoints = resolver.resolve(asio::ip::udp::v4(), _addressSend, std::to_string(8080));

        _socketSend.send_to(asio::buffer(data.data(), data.length()), *endpoints.begin());
    }

    void UDPClient::send_data_to(const std::string& data, std::string host, std::string port) {
        asio::ip::udp::resolver::results_type endpoint = _resolver.resolve(asio::ip::udp::v4(), host, port);
        asio::ip::udp::socket socket(_io_context);
        socket.open(asio::ip::udp::v4());
        socket.send_to(asio::buffer(data.data(), data.length()), *endpoint.begin());
    }

    void UDPClient::stop()
    {
        this->send_data_to("stop", _addressRecv, std::to_string(_portRecv));
        _socketRecv.close();
        _socketSend.close();
        _io_context.stop();
    }

    std::vector<std::string> UDPClient::split(std::string s, std::string delimiter)
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
