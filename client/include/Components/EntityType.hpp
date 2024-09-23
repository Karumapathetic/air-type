/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** EntityType
*/

#pragma once

#include "IComponent.hpp"

class EntityType : public IComponent {
    public:
        EntityType();
        ~EntityType();

        getType() { return type; }
        getIsPlayer() { return isPlayer; }
        setType(std::string type) { this->type = type; }
        setIsPlayer(bool isPlayer) { this->isPlayer = isPlayer; }
    protected:
    private:
        std::string type;
        bool isPlayer;
};
