/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#pragma once

#include <thread>
#include <cstring>
#include <unordered_map>

#include "AClient.hpp"
#include "RequestsFactory.hpp"
#include "ICore.hpp"
#include "DLLoader.hpp"

class Client : virtual public Network::AClient<Network::RequestsTypes> {
    public:
        Client(std::string host, const std::string& coreLibPath);
        ~Client();

        void init();
        void run();
        void stop();

        void handleData();
        void checkForInput();
        void addPosEventInCore(Network::Request<Network::RequestsTypes> request);

    protected:
    private:
        Network::RequestsFactory<Network::RequestsTypes> _factory;
        DLLoader<Graphics::ICore> _coreLoader;
        std::unique_ptr<Graphics::ICore> _core;
        bool _isClientRunning;
        int _id = 0;
};
