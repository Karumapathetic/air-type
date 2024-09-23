/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Power
*/

#pragma once

#include "IComponent.hpp"

class Power : public IComponent {
    public:
        Power();
        ~Power();

        getDamage() { return damage; }
        getAmplifier() { return amplifier; }
        setDamage(float damage) { this->damage = damage; }
        setAmplifier(float amplifier) { this->amplifier = amplifier; }
    protected:
    private:
        float damage;
        float amplifier;
};
