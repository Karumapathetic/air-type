/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client
*/

#pragma once

#include <thread>
#include <unordered_map>

#include "UDPClient.hpp"
#include "ICore.hpp"
#include "DLLoader.hpp"

class Client {
    public:
        Client(std::string host, const std::string& coreLibPath);
        ~Client();

        void init();
        void run();
        void stop();

        void handleData();
        std::vector<std::string> split(std::string s, std::string delimiter);
        std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> _commands;

        void checkForInput();

    protected:
    private:
        DLLoader<Graphics::ICore> _coreLoader;
        std::unique_ptr<Graphics::ICore> _core;

        Network::UDPClient _client;
        bool _isClientRunning;
        std::thread _networkThread;
        std::string _id;

        void connexionAccepted(std::vector<std::string> command);
        void disconnexionAccepted(std::vector<std::string> command);
        void setSpritePos(std::vector<std::string> command);
        void invalidCommand(std::vector<std::string> command);
        void connexionRefused(std::vector<std::string> command);
        void serverCrashed(std::vector<std::string> command);
};
