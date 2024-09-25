/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** backgroundEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    void backgroundHandler(Coordinator &gCoordinator, u_int32_t entity);
}
