/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Life
*/

#pragma once

#include "IComponent.hpp"

class Life : public IComponent {
    public:
        Life();
        ~Life();

        getHealth() { return health; }
        getArmor() { return armor; }
        setHealth(float health) { this->health = health; }
        setArmor(float armor) { this->armor = armor; }
    protected:
    private:
        float health;
        float armor;
};
