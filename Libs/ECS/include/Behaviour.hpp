/*
** EPITECH PROJECT, 2024
** Air-type
** File description:
** Behaviour
*/

#pragma once

#include "Coordinator.hpp"
namespace ECS {
    void behaviour(Coordinator& _coordinator);
    void handleMovement(Coordinator& _coordinator, Entity entity, std::string action);
    bool createMissile(Coordinator& _coordinator, Entity entity);
}
