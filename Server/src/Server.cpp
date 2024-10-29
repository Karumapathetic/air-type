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
}

Server::~Server()
{
}

void Server::init()
{
}

void Server::run()
{
    while(_isServerRunning) {
        update();
    }
}

void Server::update()
{
    if (_isServerRunning) {
        _coordinator.updateSystems();
        _coordinator.updateGame();
        for (auto entity: _coordinator.getEntities()) {
            if (_coordinator.getEntityUpdated(entity)) {
                std::cout << "Entity updated are treated" << std::endl;
                if (_coordinator.hasComponent(entity, _coordinator.getComponentType<ECS::Spacial>())) {
                    auto &spacial = _coordinator.getComponent<ECS::Spacial>(entity);
                    std::cout << _coordinator.getEntityName(entity) << " - " << entity << " - " << spacial.position.x << " - " << spacial.position.y << std::endl;
                    auto request = _factory.createPositionsRequests(_coordinator.getEntityName(entity), entity, spacial.position.x, spacial.position.y);
                    this->sendRequestToAllClients(request);
                }
                _coordinator.setEntityUpdated(entity, false);
            }
        }
        while (!this->_incomingRequests.isEmpty()) {
            auto request = this->_incomingRequests.popFront();
            onRequestReceived(request.remoteConnection, request.request);
        }
    } else
        this->stop();
}

void Server::onRequestReceived(std::shared_ptr<Network::UDPConnection<Network::RequestsTypes>> client, Network::Request<Network::RequestsTypes> &request)
{
    switch (request.header.id) {
        case Network::RequestsTypes::SetInput:
            this->inputReceive(_factory.transformInputRequest(request));
            break;
        case Network::RequestsTypes::LaunchGame:
            break;
        default:
            break;
    }
}

void Server::inputReceive(Network::Input input)
{
    switch (input.action) {
        case Network::InputActions::UP:
            std::cout << "UP" << std::endl;
            _coordinator.addEvent(input.clientID, "up");
            break;
        case Network::InputActions::DOWN:
            std::cout << "DOWN" << std::endl;
            _coordinator.addEvent(input.clientID, "down");
            break;
        case Network::InputActions::LEFT:
            std::cout << "LEFT" << std::endl;
            _coordinator.addEvent(input.clientID, "left");
            break;
        case Network::InputActions::RIGHT:
            std::cout << "RIGHT" << std::endl;
            _coordinator.addEvent(input.clientID, "right");
            break;
        case Network::InputActions::SHOOT:
            std::cout << "SHOOT" << std::endl;
            _coordinator.addEvent(input.clientID, "shoot");
            break;
        default:
            break;
    }
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
