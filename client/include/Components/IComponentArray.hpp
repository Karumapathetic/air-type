/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IComponentArray.hpp
*/

#pragma once

#include "EcsValues.hpp"

class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
};
