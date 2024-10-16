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
    }

    void Game::DrawSprites()
    {
        for (EntityData entity : entities) {
            if (entity.priority != -1.0f) {
                DrawTexturePro(entity.texture, entity.crop, {entity.position.x, entity.position.y, entity.scale.x, entity.scale.y}, {0.0f, 0.0f}, 0.0f, WHITE);
            }
        }
    }

    bool Game::ExtractValues(const std::string& params, const std::string& key, std::vector<float>& values, int numValues) {
        size_t keyIndex = params.find(key);
        if (keyIndex != std::string::npos) {
            size_t endPos = params.find(';', keyIndex);
            std::string extractedValues = params.substr(keyIndex + key.length(), endPos - (keyIndex + key.length()));
            std::string format;
            for (int i = 0; i < numValues; ++i) {
                format += "%f";
                if (i < numValues - 1) {
                    format += ",";
                }
            }
            values.resize(numValues);
            int result = sscanf(extractedValues.c_str(), format.c_str(), &values[0], &values[1], &values[2], &values[3]);
            return result == numValues;
        }
        return false;
    }

    void Game::CreateEntity(int id, const std::string& params) {
        if (id < 0 || id >= MAX_ENTITIES) return;

        std::vector<float> values;

        if (ExtractValues(params, "position:", values, 2)) {
            entities[id].position = {values[0], values[1]};
        } else {
            entities[id].position = {0, 0};
        }

        size_t textureIndex = params.find("texture:");
        if (textureIndex != std::string::npos) {
            size_t endPos = params.find(';', textureIndex);
            std::string texturePath = params.substr(textureIndex + 8, endPos - (textureIndex + 8));
            if (texturePath.find("player") != std::string::npos) {
                entities[id].texture = LoadTexture("Libs/Graphics/assets/texture/PlayerShip.gif");
                entities[id].scale = {86, 48};
                entities[id].crop = {0, 0, 32, 16};
                entities[id].priority = {1};
            } else if (texturePath.find("enemy") != std::string::npos) {
                entities[id].texture = LoadTexture("Libs/Graphics/assets/texture/EnemyShip.gif");
                entities[id].scale = {86, 48};
                entities[id].crop = {0, 0, 32, 16};
                entities[id].priority = {1};
            }  else if (texturePath.find("missile") != std::string::npos) {
                entities[id].texture = LoadTexture("Libs/Graphics/assets/texture/MissileKill.gif");
                entities[id].scale = {40, 40};
                entities[id].crop = {0, 0, 100, 100};
                entities[id].priority = {1};
            } else {
                entities[id].texture = {};
                entities[id].scale = {1, 1};
                entities[id].crop = {0, 0, 1, 1};
                entities[id].priority = {0};
            }
        }

        std::cout << "Entité ID: " << id << " créée avec succès:" << std::endl;
        std::cout << "Position: (" << entities[id].position.x << ", " << entities[id].position.y << ")" << std::endl;
        std::cout << "Échelle: (" << entities[id].scale.x << ", " << entities[id].scale.y << ")" << std::endl;
        std::cout << "Crop: (" << entities[id].crop.x << ", " << entities[id].crop.y << ", " 
                  << entities[id].crop.width << ", " << entities[id].crop.height << ")" << std::endl;
        std::cout << "Priorité: " << entities[id].priority << std::endl;
        std::cout << "Texture: " << (entities[id].texture.id ? "chargée" : "non chargée") << std::endl;
    }

    void Game::UpdateEntity(Entity id, const std::string& params)
    {
        if (id < 0 || id >= MAX_ENTITIES) return;
        std::vector<float> values;

        if (entities[id].priority == -1.0f) {
            CreateEntity(id, params);
            return;
        }

        if (ExtractValues(params, "position:", values, 2)) {
            entities[id].position = {values[0], values[1]};
        }
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
