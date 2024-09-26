/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IComponentArray.hpp
*/

#pragma once

#include "ECSValues.hpp"

namespace ECS {
    class IComponentArray {
        public:
            virtual ~IComponentArray() = default;
            virtual void entityDestroyed(Entity entity) = 0;
    };
}