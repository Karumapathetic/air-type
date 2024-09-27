/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Engine.hpp
*/

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Coordinator.hpp"
#include "Components.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Missile.hpp"
#include "Background.hpp"
#include "Settings.hpp"
#include "Collectible.hpp"

namespace ECS {
    class EntityFactory {
        public:
            EntityFactory();

            void createEntity(Coordinator &gCoordinator, const std::string &type, std::uint32_t entity);

        private:
            std::unordered_map<std::string, std::function<void(Coordinator&, std::uint32_t)>> entityHandlers;
    };

    Coordinator mainEngine();
}