/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>
#include "UDPClient.hpp"

int main (int argc, char const* const* argv) {
    if ((argc == 2 && argv[1] == "--help") || (argc < 2 || argc > 3)) {
        std::cout << "Usage : ./r-type_client <host> <port>" << std::endl;
        return 0;
    }

    try {
        Network::UDPClient udpClient(argv[1], std::atoi(argv[2]));
        bool stop = false;
        std::thread clientThread(&Network::UDPClient::receive_data, &udpClient, &stop);
        std::string input;

        while (!stop) {
            std::getline(std::cin, input);
            if (input == "exit")
                stop = true;
            else
                udpClient.send_data(input.data());
        }
        if (clientThread.joinable())
            clientThread.join();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
