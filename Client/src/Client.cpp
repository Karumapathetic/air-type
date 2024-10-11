/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client() : _client("127.0.0.1", 8081)
{
    _isClientRunning = true;
}

Client::~Client()
{
}

void Client::init()
{
    _networkThread = std::thread(&Network::UDPClient::receive_data, &_client, &_isClientRunning);
    _core.InitGraphics();
}

void Client::run()
{
    while (_isClientRunning) {
        _core.Caillou(&_isClientRunning);
    }
    this->stop();
}

void Client::stop()
{
    _core.CloseGraphics();
}
