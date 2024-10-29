/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string host) : Network::AClient<Network::RequestsTypes>()
{
    _isClientRunning = true;

    auto createCoreFunc = _coreLoader.getFunction<Graphics::ICore*(*)()>("CreateCore");
    _core.reset(createCoreFunc());

    _commands["12"] = std::bind(&Client::connexionAccepted, this, std::placeholders::_1);
    _commands["13"] = std::bind(&Client::disconnexionAccepted, this, std::placeholders::_1);

    _commands["21"] = std::bind(&Client::setSpritePos, this, std::placeholders::_1);

    _commands["30"] = std::bind(&Client::invalidCommand, this, std::placeholders::_1);
    _commands["31"] = std::bind(&Client::connexionRefused, this, std::placeholders::_1);
    _commands["32"] = std::bind(&Client::serverCrashed, this, std::placeholders::_1);
}

Client::~Client()
{
}

void Client::init()
{
    _core->InitGame();
}

void Client::run()
{
    while (_isClientRunning) {
        _core->Caillou(&_isClientRunning);
        checkForInput();
    }
    this->stop();
}

void Client::stop()
{
    if (_networkThread.joinable())
        _networkThread.join();
    _core->getGame().getGraphics()->CloseGraphics();
}

void Client::handleData()
{
    // std::string data = _client.getQueue().pop();
    // if (data.empty())
    //     return;
    // std::cout << "Received: " << data << std::endl;
    // std::vector<std::string> parsedData = split(data, " ");
    // auto commandHandler = _commands.find(parsedData[0]);

    // if (commandHandler == _commands.end())
    //     std::cerr << "Command \"" << parsedData[0] << "\" not known" << std::endl;
    // else
    //     commandHandler->second(parsedData);
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
    for (auto &str : res)
        str.resize(strlen(str.c_str()));
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
    std::string pos = "position:" + command[3] + "," + command[4] + ";" + "texture:" + command[1] + ";";
    _core->getGame().UpdateEntity(std::stoi(command[2]), pos);
}

void Client::invalidCommand(std::vector<std::string> command)
{
    std::cout << "Invalid command" << std::endl;
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

void Client::checkForInput()
{
    if (!_core->getGame().getClientAction().empty()) {
        if (_core->getGame().getGameState() == Graphics::GameState::MENU || _core->getGame().getGameState() == Graphics::GameState::SETTINGS)
            return;
        std::string actions = "22 " + _id;
        for (auto action : _core->getGame().getClientAction()) {
            actions += " " + action;
        }
        std::cout << "Sending action: " << actions << std::endl;
        // _client.send_data(actions);
    }
}

