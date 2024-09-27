/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** enemyEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    void enemyHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
