/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ISystem
*/

#pragma once

#include <set>
#include "EcsValues.hpp"

class ISystem {
    public:
        std::set<Entity> entities;
};
