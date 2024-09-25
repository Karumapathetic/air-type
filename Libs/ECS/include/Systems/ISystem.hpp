/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ISystem
*/

#pragma once

#include <set>
#include "ECSValues.hpp"

class ISystem {
    public:
        std::set<Entity> entities;
};
