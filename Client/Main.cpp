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
        Network::UDPClient udpClient(argv[1], argv[2]);
        udpClient.add_send_queue("Hello server");
        udpClient.run();
        std::queue<std::string> test = udpClient.get_recv_queue();
        std::cout << test.front() << std::endl;
        udpClient.pop_recv_queue();
    } catch (std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}
