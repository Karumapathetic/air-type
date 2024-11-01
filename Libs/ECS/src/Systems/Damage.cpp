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
        //if (_coordinator.getFirstEvent().second.substr(0, 6) == "damage") {
        //    std::cout << "Damage update: " << _coordinator.getFirstEvent().first << " " << _coordinator.getFirstEvent().second << std::endl;
        //    this->applyDamage(_coordinator, _coordinator.getFirstEvent().first, _coordinator.getFirstEvent().second);
        //}
    }

    void Damage::applyDamage(Coordinator& _coordinator, Entity entity, const std::string &params) const
    {
        std::string otherEntity = params.substr(6, params.size());
        Entity other = std::stoi(otherEntity);
        auto &entityLife = _coordinator.getComponent<Life>(entity);
        auto &entityPower = _coordinator.getComponent<Power>(entity);
        auto &otherLife = _coordinator.getComponent<Life>(other);
        auto &otherPower = _coordinator.getComponent<Power>(other);
        entityLife.health -= otherPower.damage;
        otherLife.health -= entityPower.damage;
        if (entityLife.health <= 0) {
            _coordinator.addEvent(entity, "killed");
        } else if (otherLife.health <= 0) {
            _coordinator.addEvent(other, "killed");
        }
        _coordinator.removeFirstEvent();
    }
}
