/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Killed
*/

#pragma once

#include <iostream>
#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the killed of entities.
     */
    class Killed : public ISystem {
        public:
            void update( Coordinator& _coordinator) override;
            void applyKilled(Coordinator& _coordinator, const Entity entity);
        protected:
        private:
    };
}
