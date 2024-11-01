/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Killed
*/

#include "Killed.hpp"

namespace ECS {
    void Killed::update(Coordinator& _coordinator, Entity entity)
    {
        //if (_coordinator.getFirstEvent().second == "killed") {
        //    std::cout << "Killed update" << std::endl;
        //    this->applyKilled(_coordinator, _coordinator.getFirstEvent().first);
        //}
    }

    void Killed::applyKilled(Coordinator& _coordinator, const Entity entity)
    {
        _coordinator.removeFirstEvent();
        _coordinator.destroyEntity(entity);
    }
}
