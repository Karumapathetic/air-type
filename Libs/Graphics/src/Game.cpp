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
    Game::Game() : _gameState(GameState::MENU), entities(MAX_ENTITIES)
    {
        _option = new Option(*this);
        std::string params = "position:100,100;scale:86,48;texture:Libs/Graphics/assets/texture/PlayerShip.gif;crop:0,0,32,16;priority:0";
        CreateEntity(0, params);
        PrintEntities();
    }

    void Game::DrawSprites()
    {
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

    void Game::CreateEntity(Entity id, const std::string& params)
    {
        if (id < 0 || id >= MAX_ENTITIES) return;
        Vector2 position = {0, 0}, scale = {1, 1};
        Rectangle crop = {0, 0, 0, 0};
        Texture2D texture = {};
        float priority = 0;

        size_t posIndex = params.find("position:");
        if (posIndex != std::string::npos) {
            size_t endPos = params.find(';', posIndex);
            std::string newPosition = params.substr(posIndex + 4, endPos - (posIndex + 4));
            sscanf(newPosition.c_str(), "%f,%f", &position.x, &position.y);
        }
        size_t scaleIndex = params.find("scale:");
        if (scaleIndex != std::string::npos) {
            size_t endPos = params.find(';', scaleIndex);
            std::string newScale = params.substr(scaleIndex + 6, endPos - (scaleIndex + 6));
            sscanf(newScale.c_str(), "%f,%f", &scale.x, &scale.y);
        }
        size_t cropIndex = params.find("crop:");
        if (cropIndex != std::string::npos) {
            size_t endPos = params.find(';', cropIndex);
            std::string newCrop = params.substr(cropIndex + 5, endPos - (cropIndex + 5));
            sscanf(newCrop.c_str(), "%f,%f,%f,%f", &crop.x, &crop.y, &crop.width, &crop.height);
        }
        size_t textureIndex = params.find("texture:");
        if (textureIndex != std::string::npos) {
            size_t endPos = params.find(';', textureIndex);
            std::string texturePath = params.substr(textureIndex + 8, endPos - (textureIndex + 8));
            texture = LoadTexture(texturePath.c_str());
        }
        size_t priorityIndex = params.find("priority:");
        if (priorityIndex != std::string::npos) {
            size_t endPos = params.find(';', posIndex);
            std::string newPosition = params.substr(posIndex + 4, endPos - (posIndex + 4));
            sscanf(newPosition.c_str(), "%f", &priority);
        }
        entities[id].position = position;
        entities[id].scale = scale;
        entities[id].texture = texture;
        entities[id].crop = crop;
        entities[id].priority = priority;
    }

    void Game::UpdateEntity(Entity id, const std::string& params)
    {
        if (id < 0 || id >= MAX_ENTITIES) return;
        CreateEntity(id, params);
    }
    void Game::DestroyEntity(Entity id)
    {
        if (id < 0 || id >= MAX_ENTITIES) return;
        entities[id] = EntityData();
    }
    void Game::PrintEntities()
    {
        for (int i = 0; i < MAX_ENTITIES; ++i) {
            if (entities[i].position.x != 0 || entities[i].position.y != 0) {
                std::cout << "Entity ID: " << i
                          << " Position: (" << entities[i].position.x << ", " << entities[i].position.y << ")"
                          << " Scale: (" << entities[i].scale.x << ", " << entities[i].scale.y << ")"
                          << " Crop: (x: " << entities[i].crop.x << ", y: " << entities[i].crop.y 
                          << ", width: " << entities[i].crop.width << ", height: " << entities[i].crop.height << ")"
                          << " Priority : " << entities[i].priority << std::endl;
            }
        }
    }

    void Game::DrawAddOns()
    {
        if (_option->getDisplayfps()) {
            DrawFPS(10, 10);
        }
    }

    void Game::DrawGraphics()
    {
        BeginDrawing();
        ClearBackground(BLACK);
        HandleKeyboardInput();
        DrawAddOns();
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
            case Graphics::GameState::SETTINGS:
                DrawSettings();
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
