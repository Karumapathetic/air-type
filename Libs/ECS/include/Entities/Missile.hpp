/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** missileEntity.hpp
*/

#pragma once

#include "Coordinator.hpp"
#include "Components.hpp"

namespace ECS {
    void missileHandler(Coordinator &gCoordinator, u_int32_t entity);
}