/*
** EPITECH PROJECT, 2024
** R-type
** File description:
** Damage.cpp
*/

#include "Damage.hpp"

namespace ECS {
    void Damage::update( Coordinator& _coordinator, Entity entity)
    {
        this->applyDamage(_coordinator, entity);
    }

    void Damage::applyDamage(Coordinator& _coordinator, Entity entity)
    {
        auto &entityLife = _coordinator.getComponent<Life>(entity);

        entityLife.health -= entityLife.damageTaken;
        entityLife.damageTaken = 0;
        if (entityLife.health <= 0) {
            _coordinator.addEvent(entity, "destroy");
        }
    }
}
