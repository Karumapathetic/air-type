/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** CircularPathing
*/

#pragma once

#include "PathingStrategy.hpp"
#include <cmath>

namespace ECS {
    /**
     * @brief Class that handles the Circular pathing of an enemy
     * 
     */
    class CircularPathing : public PathingStrategy {
        public:
            void updatePosition(Vector2& position, const float velocity) override {
                float radius = 100.0f;
                position.x += radius * std::cos(position.x * 0.1f) * velocity;
                position.y += radius * std::sin(position.y * 0.1f) * velocity;
            }
        protected:
        private:
    };
}
