/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** EscValues.hpp
*/

#pragma once

#include <cstdint>
#include <bitset>

/**
 * @brief Namespace for the ECS library.
 * 
 * This namespace contains all the classes and functions for the ECS library.
 */
namespace ECS {
    /**
     * @brief Type alias for an entity identifier.
     * 
     * An entity is an object in the ECS system. It is represented by a unique identifier.
     */
    using Entity = std::uint32_t;
    
    /**
     * @brief Maximum number of entities.
     * 
     * This constant defines the maximum number of entities that can be created in the ECS system.
     */
    const Entity MAX_ENTITIES = 1000;

    /**
     * @brief Type alias for a component type.
     * 
     * A component is a piece of data that is associated with an entity. It is represented by a unique identifier.
     */
    using ComponentType = std::uint8_t;
    
    /**
     * @brief Maximum number of components.
     * 
     * This constant defines the maximum number of components that can be created in the ECS system.
     */
    const ComponentType MAX_COMPONENTS = 32;

    /**
     * @brief Type alias for a signature.
     * 
     * A signature is a bitset that represents the components associated with an entity.
     */
    using Signature = std::bitset<MAX_COMPONENTS>;
}
