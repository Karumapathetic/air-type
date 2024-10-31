/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** PathingStrategy
*/

#pragma once

#include "Components.hpp"

namespace ECS {
    struct Vector2;

    /**
     * @brief Class for handling the pathing of enemies
     * 
     * Has only one function updatePosition to update the position depending on the pathing of the enemy.
     * 
     */
    class PathingStrategy {
        public:
            virtual ~PathingStrategy() = default;
            virtual void updatePosition(Vector2 &pos, const float velocity) = 0;
        protected:
        private:
    };
}
