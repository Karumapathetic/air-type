/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Heal
*/

#include "Heal.hpp"

namespace ECS {
    void Heal::update( Coordinator& _coordinator, Entity entity)
    {
        if (_coordinator.getFirstEvent().second == "heal") {
            std::cout << "Heal update" << std::endl;
            _coordinator.removeFirstEvent();
        }
    }
}
