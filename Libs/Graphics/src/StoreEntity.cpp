/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** StoreEntity
*/

#include "Game.hpp"

namespace Graphics {
    float Game::GetNumberOfClients() const {
        float result = 0;
        for (auto entity: _entities) {
            if (entity.second.name == "player")
                result += 1;
        }
        return result;
    }

    void Game::CreateEntity(Entity id, const std::string& params) {
        if (id < 0 || id >= MAX_ENTITIES) return;

        size_t positionIndex = params.find("position:");
        if (positionIndex != std::string::npos) {
            size_t endPos = params.find(';', positionIndex);
            std::string positionValues = params.substr(positionIndex + 9, endPos - (positionIndex + 9));

            size_t commaPos = positionValues.find(',');
            if (commaPos != std::string::npos) {
                std::string xPos = positionValues.substr(0, commaPos);
                std::string yPos = positionValues.substr(commaPos + 1);

                float x = std::stof(xPos);
                float y = std::stof(yPos);

                _entities[id].position = {x, y};

            }
        } else {
            _entities[id].position = {0, 0};
        }

        size_t textureIndex = params.find("texture:");
        if (textureIndex != std::string::npos) {
            size_t endPos = params.find(';', textureIndex);
            std::string texturePath = params.substr(textureIndex + 8, endPos - (textureIndex + 8));
            if (texturePath.find("player") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/PlayerShip.gif");
                _entities[id].scale = {86, 48};
                _entities[id].crop = {66, 35 * GetNumberOfClients(), 33, 16};
                _entities[id].priority = {1};
                _entities[id].name = "player";
            } else if (texturePath.find("pata-pata") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/enemy_pata-pata.png");
                _entities[id].scale = {66, 72};
                _entities[id].crop = {0, 0, 33, 36};
                _entities[id].priority = {1};
                _entities[id].name = "pata-pata";
            } else if (texturePath.find("win") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/enemy_win.gif");
                _entities[id].scale = {44, 45};
                _entities[id].crop = {0, 0, 33, 34};
                _entities[id].priority = {1};
                _entities[id].name = "win";
            } else if (texturePath.find("bug") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/enemy_pata-pata.png");
                _entities[id].scale = {86, 48};
                _entities[id].crop = {0, 0, 33, 36}; //temporary
                _entities[id].priority = {1};
                _entities[id].name = "bug";
            } else if (texturePath.find("wick") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/enemy_wick.gif");
                _entities[id].scale = {32, 28};
                _entities[id].crop = {0, 0, 17, 15};
                _entities[id].priority = {1};
                _entities[id].name = "wick";
            } else if (texturePath.find("geld") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/enemy_pata-pata.png");
                _entities[id].scale = {86, 48};
                _entities[id].crop = {0, 0, 33, 36}; //temporary
                _entities[id].priority = {1};
                _entities[id].name = "geld";
            } else if (texturePath.find("missile") != std::string::npos) {
                _graphics->LoadTextureFromFile(id, "Libs/Graphics/assets/texture/missile.gif");
                _entities[id].scale = {60, 12};
                _entities[id].crop = {0, 0, 81, 18};
                _entities[id].priority = {1};
                _entities[id].name = "missile";
            } else {
                _entities[id].scale = {1, 1};
                _entities[id].crop = {0, 0, 1, 1};
                _entities[id].priority = {0};
            }
        }

        std::cout << "Entité ID: " << id << " créée avec succès:" << std::endl;
        std::cout << "Name : " << _entities[id].name << std::endl;
        std::cout << "Position: (" << _entities[id].position.x << ", " << _entities[id].position.y << ")" << std::endl;
        std::cout << "Échelle: (" << _entities[id].scale.x << ", " << _entities[id].scale.y << ")" << std::endl;
        std::cout << "Crop: (" << _entities[id].crop.x << ", " << _entities[id].crop.y << ", " 
                  << _entities[id].crop.width << ", " << _entities[id].crop.height << ")" << std::endl;
        std::cout << "Priorité: " << _entities[id].priority << std::endl;
    }

    void Game::UpdateEntity(Entity id, const std::string& params)
    {
        if (id < 0 || id >= MAX_ENTITIES) return;
        std::vector<float> values;

        if (_entities[id].priority == -1.0f) {
            CreateEntity(id, params);
            return;
        }

        size_t positionIndex = params.find("position:");
        if (positionIndex != std::string::npos) {
            size_t endPos = params.find(';', positionIndex);
            std::string positionValues = params.substr(positionIndex + 9, endPos - (positionIndex + 9));

            size_t commaPos = positionValues.find(',');
            if (commaPos != std::string::npos) {
                std::string xPos = positionValues.substr(0, commaPos);
                std::string yPos = positionValues.substr(commaPos + 1);

                float x = std::stof(xPos);
                float y = std::stof(yPos);

                Vector2 oldPos = _entities[id].position;
                _entities[id].position = {x, y};
                if (_entities[id].name == "player") {
                    if (oldPos.x != _entities[id].position.x || oldPos.y != _entities[id].position.y)
                        AnimateEntity(oldPos, _entities[id].position, id);
                }
            }
        }
    }

    void Game::DestroyEntity(Entity id)
    {
        if (id < 0 || id >= MAX_ENTITIES || _entities[id].priority == -1.0f) return;
        _entities[id] = EntityData();
        _graphics->UnloadTextureById(id);
        std::cout << "Entité ID: " << id << " détruite avec succès" << std::endl;
    }

    void Game::PrintEntities()
    {
        for (int i = 0; i < MAX_ENTITIES; ++i) {
            if (_entities[i].position.x != 0 || _entities[i].position.y != 0) {
                std::cout << "Entity ID: " << i
                          << " Position: (" << _entities[i].position.x << ", " << _entities[i].position.y << ")"
                          << " Scale: (" << _entities[i].scale.x << ", " << _entities[i].scale.y << ")"
                          << " Crop: (x: " << _entities[i].crop.x << ", y: " << _entities[i].crop.y 
                          << ", width: " << _entities[i].crop.width << ", height: " << _entities[i].crop.height << ")"
                          << " Priority : " << _entities[i].priority << std::endl;
            }
        }
    }
}
