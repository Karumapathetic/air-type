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
        std::cout << "Port: " << _port << std::endl;
    }

    UDPServer::~UDPServer() {
    }

    void UDPServer::receive_data(bool *stop) {
        while (*stop) {
            std::string recv_buf(1024, '\0');
            asio::ip::udp::endpoint sender_endpoint;
            size_t len = _socket.receive_from(asio::buffer(recv_buf.data(), 1024), sender_endpoint);
            recv_buf.resize(len);
            _recv_queue.push(recv_buf);
            std::cout << "Received: \"" << recv_buf << "\" from : \"" << sender_endpoint.address() << ":" << sender_endpoint.port() << "\"" << std::endl;
        }
    }

    void UDPServer::send_data(const std::string& data, std::string host, std::string port) {
        asio::ip::udp::resolver::results_type endpoint = _resolver.resolve(asio::ip::udp::v4(), host, port);
        asio::ip::udp::socket socket(_io_context);
        socket.open(asio::ip::udp::v4());
        socket.send_to(asio::buffer(data.data(), data.length()), *endpoint.begin());
    }

    void UDPServer::stop()
    {
        this->send_data("stop", _address, std::to_string(_port));
        _socket.close();
        _io_context.stop();
    }

    SafeQueue<std::string>& UDPServer::getQueue()
    {
        return _recv_queue;
    }
}
