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
    /**
     * @brief Interface for the systems.
     * 
     * This interface is used to create the systems for the ECS.
     * 
     */
    class ISystem {
        public:
            std::set<Entity> entities;
    };
}
