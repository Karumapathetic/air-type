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
    _playerConnection = false;
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
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = end - start;
    if (_isServerRunning) {
        if (!_playerConnection) {
            std::cout << "Action 1" << std::endl;
            behaviour(_coordinator);
            end = std::chrono::high_resolution_clock::now(); elapsed = end - start; std::cout << "Elapsed: " << elapsed.count() << std::endl; start = end;
            std::cout << "Action 2" << std::endl;
            _coordinator.updateSystems();
            end = std::chrono::high_resolution_clock::now(); elapsed = end - start; std::cout << "Elapsed: " << elapsed.count() << std::endl; start = end;
            std::cout << "Action 3" << std::endl;
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
            end = std::chrono::high_resolution_clock::now(); elapsed = end - start; std::cout << "Elapsed: " << elapsed.count() << std::endl; start = end;
            while (!this->_incomingRequests.isEmpty()) {
                auto request = this->_incomingRequests.popFront();
                onRequestReceived(request.remoteConnection, request.request);
            }
        }
    } else
        this->stop();
}

bool Server::onClientConnection(std::shared_ptr<Network::UDPConnection<Network::RequestsTypes>> client)
{
    _playerConnection = true;
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
    _playerConnection = false;
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
