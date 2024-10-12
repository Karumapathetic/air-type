/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#pragma once

#include <thread>

#include "UDPClient.hpp"
#include "Core.hpp"

class Client {
    public:
        Client(std::string host);
        ~Client();

        void init();
        void run();
        void stop();

    protected:
    private:
        Graphics::Core _core;
        Network::UDPClient _client;
        bool _isClientRunning;
        std::thread _networkThread;
};
