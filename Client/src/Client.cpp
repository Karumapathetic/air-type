/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string host) : _client(host)
{
    _isClientRunning = true;
}

Client::~Client()
{
}

void Client::init()
{
    _networkThread = std::thread(&Network::UDPClient::receive_data, &_client, &_isClientRunning);
    // _core.InitGraphics();
}

void Client::run()
{
    std::string input;
    while (_isClientRunning) {
        //_core.Caillou(&_isClientRunning);
        std::getline(std::cin, input);
        if (input == "exit")
            _isClientRunning = false;
        else
            _client.send_data(input);
    }
    this->stop();
}

void Client::stop()
{
    _client.stop();
    if (_networkThread.joinable())
        _networkThread.join();
    // _core.CloseGraphics();
}
