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
            void update(Coordinator& _coordinator, Entity entity) override;
            void applyDamage(Coordinator& _coordinator, Entity entity, const std::string &params) const;
        protected:
        private:
    };
}
