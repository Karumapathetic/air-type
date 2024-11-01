/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** update.hpp
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

namespace ECS {
    class Update : public ISystem{
        public:
            void update( Coordinator& _coordinator, Entity entity);
            void gameUpdate(Coordinator& _coordinator, Entity entity);
        protected:
        private:
    };
}
