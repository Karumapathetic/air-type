/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Game
*/

#include <iostream>
#include <ctime>
#include "raylib.h"
#include "Game.hpp"
#include "Draw.hpp"

namespace Graphics {
    void Game::InitCoordinator() {
        _coordinator = ECS::Coordinator::initEngine();
    }

    void Game::DrawSprites() {
        auto drawSystem = _coordinator.getCoordSystem<ECS::Draw>();
        ECS::Signature texturesSignature = _coordinator.getComponentType<ECS::Images>();
        for (const ECS::Entity& entity : _coordinator.getEntities()) {
            auto entityName = _coordinator.getEntityName(entity);
            ECS::Signature entitySignature = _coordinator.getEntitySignature(entity);
            if ((entitySignature & texturesSignature) == texturesSignature) {
                ECS::Images entityImages = _coordinator.getComponent<ECS::Images>(entity);
                ECS::Spacial entitySpacial = _coordinator.getComponent<ECS::Spacial>(entity);
                drawSystem->RenderEntitiesWithImages(entityImages.texture, entityImages.cropArea, entitySpacial.position, entitySpacial.scale);
            }
        }
    }

    void Game::DrawGraphics() {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawSprites();
        HandleKeyboardInput();
        switch (getGameState()) {
            case Graphics::GameState::MENU:
                DrawMenu();
                break;
            case Graphics::GameState::GAME:
                DrawGame();
                break;
            case Graphics::GameState::PAUSE:
                DrawPause();
                break;
            case Graphics::GameState::GAMEOVER:
                break;
            case Graphics::GameState::WIN:
                break;
            default:
                break;
        }
        EndDrawing();
    }
}
