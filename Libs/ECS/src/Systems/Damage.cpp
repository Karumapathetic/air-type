/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Damage.cpp
*/

#include "Damage.hpp"

namespace ECS {
    void Damage::update( Coordinator& _coordinator)
    {
        if (_coordinator.getFirstEvent().second == "damage") {
            std::cout << "Damage update" << std::endl;
            _coordinator.removeFirstEvent();
        }
    }
}
