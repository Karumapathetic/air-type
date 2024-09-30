/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ISystem
*/

#pragma once

#include <set>
#include "ECSValues.hpp"

namespace ECS {
    class ISystem {
        public:
            std::set<Entity> entities;
    };
}