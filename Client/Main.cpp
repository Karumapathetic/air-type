/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>

#include "Client.hpp"

int main(void) {
    try {
        Client client;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
