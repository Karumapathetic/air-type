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
            /**
             * @brief Updates the system.
             * 
             * This function is responsible for updating the system. It is called once per frame.
             * 
             * @return void
             */
            virtual void update() = 0;
            std::set<Entity> entities;
    };
}
