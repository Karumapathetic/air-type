/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server
*/

#include "Server.hpp"

Server::Server() : Network::AServer<Network::RequestsTypes>()
{
    _isServerRunning = true;

    _commands["10"] = std::bind(&Server::connect, this, std::placeholders::_1);
    _commands["11"] = std::bind(&Server::disconnect, this, std::placeholders::_1);

    _commands["22"] = std::bind(&Server::getUserInput, this, std::placeholders::_1);

    _commands["32"] = std::bind(&Server::clientCrash, this, std::placeholders::_1);
}

Server::~Server()
{
}

void Server::init()
{
}

void Server::run()
{
    while (_isServerRunning) {
        auto updateSystem = _coordinator.getCoordSystem<ECS::Update>();
        updateSystem->UpdatePositions(_coordinator, [this](const std::string& data) { sendToClients(data); });
        auto collisionSystem = _coordinator.getCoordSystem<ECS::Collision>();
        collisionSystem->detectCollision(_coordinator);
    }
    this->stop();
}

void Server::stop()
{
    if (_networkThread.joinable())
        _networkThread.join();
}

void Server::sendECSData()
{
    // for (auto client : _clients) {
    //     for (auto entity : _coordinator.getEntities()) {
    //         if (_coordinator.getEntityName(entity) == "settings")
    //             continue;
    //         auto &spacial = _coordinator.getComponent<ECS::Spacial>(entity);
    //         std::string name = _coordinator.getEntityName(entity);
    //         std::cout << "Sending: 21 " + name + " " + std::to_string(entity) + " " + std::to_string(spacial.position.x) + " " + std::to_string(spacial.position.y) << std::endl;
    //         _server.send_data("21 " + name + " " + std::to_string(entity) + " " + std::to_string(spacial.position.x) + " " + std::to_string(spacial.position.y), client.s_address, client.s_port);
    //     }
    // }
}

void Server::handleData()
{
    std::cout << "Handling data" << std::endl;

    // std::string data = _server.getQueue().pop();
    // if (data.empty())
    //     return;
    // std::vector<std::string> parsedData = split(data, " ");
    // auto commandHandler = _commands.find(parsedData[0]);

    // if (commandHandler == _commands.end())
    //     std::cerr << "Command \"" << parsedData[0] << "\" not known" << std::endl;
    // else
    //     commandHandler->second(parsedData);
}

std::vector<std::string> Server::split(std::string s, std::string delimiter)
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

void Server::connect(std::vector<std::string> command)
{
    // if (command.size() != 3) {
    //     std::cerr << "Command is not valid" << std::endl;
    // }
    // std::string address = command[1];
    // std::string port = command[2];
    // bool isRegistered = false;
    // for (auto client : _clients) {
    //     if (client.s_address == address && client.s_port == port)
    //         isRegistered = true;
    // }
    // if (!isRegistered && _clients.size() < 3) {
    //     Network::Client_t newClient;
    //     newClient.s_address = address;
    //     newClient.s_port = port;
    //     newClient.s_id = _clients.size() + 1;
    //     auto newEntity = _coordinator.createEntity("player");
    //     _coordinator.initEntities();
    //     auto &entitypePlayer = _coordinator.getComponent<ECS::EntityTypes>(newEntity);
    //     entitypePlayer.id = newClient.s_id;
    //     _clients.push_back(newClient);
    //     // _server.send_data("12 " + std::to_string(newEntity), newClient.s_address, newClient.s_port);
    //     sendECSData();
    //     this->sendToClients("21 " + _coordinator.getEntityName(newEntity) + " " + std::to_string(newEntity) + " " + std::to_string(_coordinator.getComponent<ECS::Spacial>(newEntity).position.x) + " " + std::to_string(_coordinator.getComponent<ECS::Spacial>(newEntity).position.y));
    // }
}

void Server::disconnect(std::vector<std::string> command)
{
    // if (command.size() != 2) {
    //     return;
    // }
    // std::string clientId = command[1];
    // for (auto client : _clients) {
    //     if (std::atoi(clientId.c_str()) == client.s_id) {
    //         // _server.send_data("13 ", client.s_address, client.s_port);
    //         _clients.erase(std::remove_if(
    //             _clients.begin(), _clients.end(),
    //             [&clientId](const Network::Client_t& item) {
    //                 return item.s_id == std::atoi(clientId.c_str());
    //             }
    //         ));
    //     }
    // }
}

void Server::getUserInput(std::vector<std::string> command)
{
    // if (command.size() < 3) {
    //     std::cerr << "Command is not valid" << std::endl;
    //     return;
    // }
    // bool positionUpdated = false;
    // ECS::Entity entityId = std::stoi(command[1]);

    // for (int i = 2; i < command.size(); i++) {
    //     std::string action = command[i];
    //     if (action == "shoot") {
    //         auto shootSystem = _coordinator.getCoordSystem<ECS::Shoot>();
    //         shootSystem->MissileShoot(_coordinator, entityId);
    //     } else {
    //         auto moveSystem = _coordinator.getCoordSystem<ECS::Move>();
    //         auto entities = _coordinator.getEntities();
    //         moveSystem->MoveEntities(_coordinator, entityId, action);
    //         positionUpdated = true;
    //     }
    // }
    // if (positionUpdated) {
    //     this->sendToClients("21 " + _coordinator.getEntityName(entityId) + " " + std::to_string(entityId) + " " + std::to_string(_coordinator.getComponent<ECS::Spacial>(entityId).position.x) + " " + std::to_string(_coordinator.getComponent<ECS::Spacial>(entityId).position.y));        
    // }
}

void Server::clientCrash(std::vector<std::string> command)
{
    // if (command.size() != 2) {
    //     return;
    // }
    // std::string clientId = command[1];
    // _clients.erase(std::remove_if(
    //     _clients.begin(), _clients.end(),
    //     [&clientId](const Network::Client_t& item) {
    //         return item.s_id == std::atoi(clientId.c_str());
    //     }
    // ));
}

void Server::sendToClients(const std::string& data)
{
    // for (auto client : _clients) {
    //     // _server.send_data(data, client.s_address, client.s_port);
    // }
}
