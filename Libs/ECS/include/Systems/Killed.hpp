/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Killed
*/

#pragma once

#include <iostream>
#include "ISystem.hpp"

namespace ECS {
    /**
     * @brief System that handles the killed of entities.
     */
    class Killed : public ISystem {
        public:
            void update() {std::cout << "Killed" << std::endl;}
        protected:
        private:
    };
}
