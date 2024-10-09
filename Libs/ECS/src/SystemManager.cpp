/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SystemManager
*/

#include "SystemManager.hpp"

namespace ECS {
    void SystemManager::entityDestroyed(Entity entity)
    {
        for (auto const& pair : systems) {
            auto const& system = pair.second;
            system->entities.erase(entity);
        }
    }

    void SystemManager::entitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for (auto const& pair : systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            if ((entitySignature & systemSignature) == systemSignature) {
                system->entities.insert(entity);
            } else {
                system->entities.erase(entity);
            }
        }
    }
}
