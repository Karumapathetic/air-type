/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Player
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

class Player : public IEntity {
    public:
        Player();
        ~Player();
    protected:
    private:
        Spacial *_spacial;
        Power *_power;
        Life *_life;
        Speed *_speed;
        Image *_image;
        EntityType *_entityType;
};
