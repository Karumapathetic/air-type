/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Shoot
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    /**
     * @brief System that handles the shooting of entities.
     */
    class Shoot : public ISystem {
        public:
            void update( Coordinator& _coordinator);
            /**
             * @brief Shoots a missile from the entity.
             * 
             * @param coordinator The coordinator that contains the entities.
             * @param entity The entity that is shooting the missile.
             */
            bool MissileShoot(Coordinator &coordinator, Entity entity);
        protected:
        private:
    };
}
