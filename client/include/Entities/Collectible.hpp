/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Collectible
*/

#pragma once

#include "IEntity.hpp"

// Components
#include "Spacial.hpp"
#include "Speed.hpp"
#include "Image.hpp"
#include "EntityType.hpp"

class Collectible : public IEntity {
    public:
        Collectible();
        ~Collectible();
    protected:
    private:
        Spacial *_spacial;
        Speed *_speed;
        Image *_image;
        EntityType *_entityType;
};
