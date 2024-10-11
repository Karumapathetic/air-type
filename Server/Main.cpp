/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server main
*/

#include <iostream>
#include "UDPServer.hpp"

int main (int argc, char const* const* argv) {
    if (argc != 2 || (argc == 2 && argv[1] == "--help")) {
        std::cout << "Usage : ./r-type_server <port>" << std::endl;
        return 0;
    }

    try {
        Network::UDPServer udpServer("127.0.0.1", std::atoi(argv[1]));

        bool stop = false;
        std::thread serverThread(&Network::UDPServer::receive_data, &udpServer, &stop);
        std::string input;

        while (!stop) {
            std::getline(std::cin, input);
            if (input == "exit")
                stop = true;
            else
                udpServer.send_all_data(input.data());
        }
        if (serverThread.joinable())
            serverThread.join();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
