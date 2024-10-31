/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** LinearPathing
*/

#pragma once

#include "PathingStrategy.hpp"

namespace ECS {
    /**
     * @brief Class that handles the Linear pathing of an enemy
     * 
     */
    class LinearPathing : public PathingStrategy {
        public:
            void updatePosition(Vector2& position, const float velocity) override {
                position.x -= velocity; // Move left at a constant speed
            }
        protected:
        private:
    };
}
