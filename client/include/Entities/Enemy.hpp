/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Enemy
*/

#pragma once

#include "IEntity.hpp"

// Components
#include "Spacial.hpp"
#include "Power.hpp"
#include "Life.hpp"
#include "Speed.hpp"
#include "Image.hpp"
#include "EntityType.hpp"

class Enemy : public IEntity {
    public:
        Enemy();
        ~Enemy();
    protected:
    private:
        Spacial *_spacial;
        Power *_power;
        Life *_life;
        Speed *_speed;
        Image *_image;
        EntityType *_entityType;
};
