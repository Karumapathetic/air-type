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

#include "Coordinator.hpp"
#include "AServer.hpp"

#include "Move.hpp"
#include "Shoot.hpp"
//#include "Collision.hpp"

class Server : virtual public Network::AServer<Network::RequestsTypes> {
    public:
        Server();
        ~Server();

        void init();
        void run();
        void stop();

        void sendECSData(void);
        void handleData();
        void sendToClients(const std::string& data);
        std::vector<std::string> split(std::string s, std::string delimiter);

    protected:
    private:
        ECS::Coordinator _coordinator;
        bool _isServerRunning;
        std::thread _networkThread;

        std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> _commands;

        void connect(std::vector<std::string> command);
        void disconnect(std::vector<std::string> command);
        void clientCrash(std::vector<std::string> command);
        void getUserInput(std::vector<std::string> command);
};
