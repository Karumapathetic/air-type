/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Entity.cpp
*/

#include "Coordinator.hpp"
#include "LinearPathing.hpp"
#include "CircularPathing.hpp"

namespace ECS {
    void patapataHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {66.0f, 72.0f}});
        gCoordinator.addComponent(entity, Power{3.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_pata-pata.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 0});
        gCoordinator.addComponent(entity, Pathing{std::make_shared<LinearPathing>()});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void winHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {44.0f, 45.0f}});
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{30000.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_win.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 1});
        gCoordinator.addComponent(entity, Pathing{std::make_shared<LinearPathing>()});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void bugHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{3.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_pata-pata.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 2});
        gCoordinator.addComponent(entity, Pathing{std::make_shared<CircularPathing>()});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void wickHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {32.0f, 28.0f}});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{1.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{8.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_wick.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 3});
        gCoordinator.addComponent(entity, Pathing{std::make_shared<CircularPathing>()});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void geldHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{30.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_pata-pata.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 4});
        gCoordinator.addComponent(entity, Pathing{std::make_shared<CircularPathing>()});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
