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
        Network::UDPServer udpServer(std::atoi(argv[1]));
        udpServer.add_send_queue("Hello client");
        udpServer.run();
        std::queue<std::string> test = udpServer.get_recv_queue();
        std::cout << test.front() << std::endl;
        udpServer.pop_recv_queue();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
