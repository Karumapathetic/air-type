/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Damage
*/

#pragma once

#include <iostream>

#include "Coordinator.hpp"
#include "ISystem.hpp"

namespace ECS {
    /**
     * @brief System that handles the damage between entities.
     */
    class Damage : public ISystem {
        public:
            void update(Coordinator& _coordinator) override;
        protected:
        private:
    };
}
