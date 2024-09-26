/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Client main
*/

#include <iostream>
#include "Game.hpp"

int main() {
    try {
        Graphics::Game game;
        game.LaunchGame();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}