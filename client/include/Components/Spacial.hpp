/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Spacial
*/

#pragma once

#include "IComponent.hpp"

class Spacial : public IComponent {
    public:
        Spacial();
        ~Spacial();

        getPos() { return pos; }
        getScale() { return scale; }
        setPos(float pos) { this->pos = pos; }
        setScale(float scale) { this->scale = scale; }
    protected:
    private:
        float pos;
        float scale;
};
