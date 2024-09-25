/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CollectibleEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    void collectibleHandler(Coordinator &gCoordinator, std::uint32_t entity);
}