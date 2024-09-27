/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>
#include "Core.hpp"

int main() {
    try {
        Graphics::Core core;
        core.LaunchGame();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}