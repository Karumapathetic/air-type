/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** EscValues.hpp
*/

#pragma once

#include <cstdint>
#include <bitset>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 1000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
