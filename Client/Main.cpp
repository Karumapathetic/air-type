/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>

#include "Client.hpp"

int main(int argc, char const* const* argv) {
    if (argc != 2) {
        std::cout << "Usage: ./r-type_client <host>" << std::endl;
        return 0;
    }
    try {
        Client client(argv[1], "./Debug/Graphics.dll");
        client.init();
        client.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
