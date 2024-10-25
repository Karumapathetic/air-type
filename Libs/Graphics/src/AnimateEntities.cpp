/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** AnimateEntities
*/

#include "Game.hpp"

namespace Graphics {
    void Game::InitializeAnimationsMap() {
        _animationMap["player"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (oldPos.y > newPos.y) {
                if (_entities[id].crop.x == _entities[id].crop.width * 4)
                    return;
                _entities[id].crop.x += _entities[id].crop.width;
            } else if (oldPos.y < newPos.y) {
                if (_entities[id].crop.x == 0)
                    return;
                _entities[id].crop.x -= _entities[id].crop.width;
            }
        };
        _animationMap["pata-pata"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 7)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        };
        _animationMap["win"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 2)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        };
        _animationMap["wick"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 7)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        };
        _animationMap["missile"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        };
        _animationMap["killed"] = [this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width)
                _entities.erase(id);
            else
                _entities[id].crop.x += _entities[id].crop.width;
        };
    }

    void Game::AnimateEntity(Vector2 oldPos, Vector2 newPos, int id)
    {
        const std::string& entityName = _entities[id].name;
        if (_animationMap.find(entityName) != _animationMap.end()) {
            _animationMap[entityName](id, oldPos, newPos);
        }
    }
}
