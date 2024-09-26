/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ennemyEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    void ennemyHandler(Coordinator &gCoordinator, std::uint32_t entity);
}
