/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server
*/

#pragma once

#include <thread>

#include "UDPServer.hpp"
#include "Coordinator.hpp"

class Server {
    public:
        Server();
        ~Server();

        void init();
        void run();
        void stop();
    protected:
    private:
        Network::UDPServer _server;
        ECS::Coordinator _coordinator;
        bool _isServerRunning;
        std::thread _networkThread;
};
