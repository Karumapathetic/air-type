/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Speed
*/

#pragma once

#include "IComponent.hpp"

class Speed : public IComponent {
    public:
        Speed();
        ~Speed();

        getVelocity() { return velocity; }
        getAcceleration() { return acceleration; }
        setVelocity(float velocity) { this->velocity = velocity; }
        setAcceleration(float acceleration) { this->acceleration = acceleration; }
    protected:
    private:
        float velocity;
        float acceleration;
};
