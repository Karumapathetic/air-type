/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server
*/

#pragma once

#include <thread>
#include <unordered_map>
#include <cstring>

#include "AServer.hpp"
#include "RequestsFactory.hpp"

#include "Coordinator.hpp"
#include "Behaviour.hpp"
#include "Move.hpp"
//#include "Collision.hpp"

class Server : virtual public Network::AServer<Network::RequestsTypes> {
    public:
        Server();
        ~Server();

        void init();
        void run();
        void update() override;

    protected:
        void onRequestReceived(std::shared_ptr<Network::UDPConnection<Network::RequestsTypes>> client, Network::Request<Network::RequestsTypes> &request) override;
        bool onClientConnection(std::shared_ptr<Network::UDPConnection<Network::RequestsTypes>> client) override;

        void inputReceive(Network::Input input);
    private:
        ECS::Coordinator _coordinator;
        Network::RequestsFactory<Network::RequestsTypes> _factory;
        bool _isServerRunning;
        bool _playerConnection;
};
