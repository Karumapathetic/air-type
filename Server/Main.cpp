/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Server main
*/

#include "Server.hpp"

int main (void) {
    try {
        Server server;
        server.init();
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
