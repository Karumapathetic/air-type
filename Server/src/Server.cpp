/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server() : _server("127.0.0.1", 8080)
{
    _isServerRunning = true;
}

Server::~Server()
{
}

void Server::init()
{
    _networkThread = std::thread(&Network::UDPServer::receive_data, &_server, &_isServerRunning);
}

void Server::run()
{
    std::string input;

    while (_isServerRunning) {
        std::getline(std::cin, input);
        if (input == "exit")
            _isServerRunning = false;
        else
            _server.send_all_data(input);
    }
    this->stop();
}

void Server::stop()
{
    _server.stop();
    if (_networkThread.joinable())
        _networkThread.join();
}
