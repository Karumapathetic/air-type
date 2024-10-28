/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Entity.cpp
*/

#include "Coordinator.hpp"

namespace ECS {
    void patapataHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{3.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_pata-pata.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 0});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void winHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{5.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{30000.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_win.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 1});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void bugHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{3.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{3.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/Bug.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 2});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void wickHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{1.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{8.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/enemy_wick.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 3});
        gCoordinator.setEntityInitialized(entity, true);
    }

    void geldHandler(Coordinator &gCoordinator, std::uint32_t entity) {
        gCoordinator.addComponent(entity, Spacial{{2000.0f, 100.0f}, {86.0f, 48.0f}});
        gCoordinator.addComponent(entity, Power{1.0f, 0.0f});
        gCoordinator.addComponent(entity, Life{30.0f, 1.0f});
        gCoordinator.addComponent(entity, Speed{2.0f, 1.0f});
        gCoordinator.addComponent(entity, Images{"Libs/Graphics/assets/texture/Geld.gif"});
        gCoordinator.addComponent(entity, EntityTypes{"enemy", 4});
        gCoordinator.setEntityInitialized(entity, true);
    }
}
