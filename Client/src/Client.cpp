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

    _commands["12"] = std::bind(&Client::connexionAccepted, this, std::placeholders::_1);
    _commands["13"] = std::bind(&Client::disconnexionAccepted, this, std::placeholders::_1);

    _commands["21"] = std::bind(&Client::setSpritePos, this, std::placeholders::_1);

    _commands["30"] = std::bind(&Client::invalidCommand, this, std::placeholders::_1);
    _commands["31"] = std::bind(&Client::connexionRefused, this, std::placeholders::_1);
    _commands["32"] = std::bind(&Client::serverCrashed, this, std::placeholders::_1);

    _client.send_data("10 " + _client.getRecvAddress() + " " + std::to_string(_client.getRecvPort()));
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
    while (_isClientRunning) {
        // Change sprite position
        //_core.Caillou(&_isClientRunning);
        if (_client.getQueue().size() > 0)
            handleData();
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

void Client::handleData()
{
    std::string data = _client.getQueue().pop();
    if (data.empty())
        return;
    std::vector<std::string> parsedData = split(data, " ");
    auto commandHandler = _commands.find(parsedData[0]);

    if (commandHandler == _commands.end())
        std::cerr << "Command \"" << parsedData[0] << "\" not known" << std::endl;
    else
        commandHandler->second(parsedData);
}

std::vector<std::string> Client::split(std::string s, std::string delimiter)
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

void Client::connexionAccepted(std::vector<std::string> command)
{
    if (command.size() != 2) {
        std::cerr << "Server did not gave id" << std::endl;
        return;
    }
    _id = command[1];
}

void Client::setSpritePos(std::vector<std::string> command)
{
    std::cout << "Set sprite pos" << std::endl;
    // Draw
}

void Client::invalidCommand(std::vector<std::string> command)
{
    std::cout << "Invalid command" << std::endl;
    return;
}

void Client::connexionRefused(std::vector<std::string> command)
{
    std::cout << "Connexion refused" << std::endl;
    _isClientRunning = false;
}

void Client::serverCrashed(std::vector<std::string> command)
{
    std::cout << "Server Crashed" << std::endl;
    _isClientRunning = false;
}

void Client::disconnexionAccepted(std::vector<std::string> command)
{
    std::cout << "Disconnexion accepted" << std::endl;
    _isClientRunning = false;
}