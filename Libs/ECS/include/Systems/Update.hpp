/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Update
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the update of entities.
     */
    class UpdateSystem : public ISystem {
        public:
            void update(Coordinator& _coordinator);
            void updatePositions(Coordinator& _coordinator);
        protected:
        private:
    };
}
