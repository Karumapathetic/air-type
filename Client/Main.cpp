/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>
#include "Core.hpp"

int main(int argc, char const* const* argv) {
    if ((argc == 2 && argv[1] == "--help") || (argc < 2 || argc > 3)) {
        std::cout << "Usage : ./r-type_client <host> <port>" << std::endl;
        return 0;
    }
    try {
        Graphics::Core core;
        core.LaunchGame();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
