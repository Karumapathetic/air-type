/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Missile
*/

#pragma once

#include "IEntity.hpp"

// Components
#include "Spacial.hpp"
#include "Power.hpp"
#include "Speed.hpp"
#include "Image.hpp"
#include "EntityType.hpp"

class Missile : public IEntity {
    public:
        Missile();
        ~Missile();
    protected:
    private:
        Spacial *_spacial;
        Power *_power;
        Speed *_speed;
        Image *_image;
        EntityType *_entityType;
};
