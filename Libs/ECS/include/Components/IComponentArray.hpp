/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** IComponentArray.hpp
*/

#pragma once

#include "ECSValues.hpp"

namespace ECS {
    /**
     * @brief An interface for an array of components of a specific type.
     * 
     * This interface is used to store components of a specific type. It provides functions
     * to insert, retrieve, and remove components from the array. It also maps entities
     * to the index of the component in the array.
     * 
     * The interface contains a pure virtual function entityDestroyed() that is called when
     * an entity is destroyed.
     * 
     */
    class IComponentArray {
        public:
            virtual ~IComponentArray() = default;
            virtual void entityDestroyed(Entity entity) = 0;
    };
}
