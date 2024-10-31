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
        for (auto entity: _coordinator.getEntities()) {
            if (_coordinator.getEntityUpdated(entity)) {
                if (_coordinator.hasComponent(entity, _coordinator.getComponentType<ECS::Spacial>())) {
                    auto &spacial = _coordinator.getComponent<ECS::Spacial>(entity);
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

bool Server::onClientConnection(std::shared_ptr<Network::UDPConnection<Network::RequestsTypes>> client)
{
    auto newEntity = _coordinator.createEntity("player");
    _coordinator.initEntities();
    auto &entityTypePlayer = _coordinator.getComponent<ECS::EntityTypes>(newEntity);
    entityTypePlayer.id = _id++;
    auto request = _factory.createConnectionAccepted(newEntity);
    this->sendRequestToClient(request, client);
    for (auto entity : _coordinator.getEntities()) {
        if (_coordinator.hasComponent(entity, _coordinator.getComponentType<ECS::Spacial>())) {
            auto &spacial = _coordinator.getComponent<ECS::Spacial>(entity);
            auto request = _factory.createPositionsRequests(_coordinator.getEntityName(entity), entity, spacial.position.x, spacial.position.y);
            this->sendRequestToClient(request, client);
        }
    }
    return true;
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
            _coordinator.addEvent(input.clientID, "up");
            break;
        case Network::InputActions::DOWN:
            _coordinator.addEvent(input.clientID, "down");
            break;
        case Network::InputActions::LEFT:
            _coordinator.addEvent(input.clientID, "left");
            break;
        case Network::InputActions::RIGHT:
            _coordinator.addEvent(input.clientID, "right");
            break;
        case Network::InputActions::SHOOT:
            _coordinator.addEvent(input.clientID, "shoot");
            break;
        default:
            break;
    }
}
