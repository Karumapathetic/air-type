/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Heal
*/

#pragma once

#include <iostream>

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the healing of entities.
     */
    class Heal : public ISystem {
        public:
            void update(Coordinator& _coordinator) override;
        protected:
        private:
    };
}
