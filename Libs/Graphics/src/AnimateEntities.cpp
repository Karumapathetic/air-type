/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** AnimateEntities
*/

#include "Game.hpp"

namespace Graphics {
    void Game::InitializeAnimationsMap() {
        _animationMap["player"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (oldPos.y > newPos.y) {
                if (_entities[id].crop.x == _entities[id].crop.width * 4)
                    return;
                _entities[id].crop.x += _entities[id].crop.width;
            } else if (oldPos.y < newPos.y) {
                if (_entities[id].crop.x == 0)
                    return;
                _entities[id].crop.x -= _entities[id].crop.width;
            }
        }, std::chrono::steady_clock::now());
        _animationMap["pata-pata"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 7)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }, std::chrono::steady_clock::now());
        _animationMap["win"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 2)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }, std::chrono::steady_clock::now());
        _animationMap["wick"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 3)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }, std::chrono::steady_clock::now());
        _animationMap["missile"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }, std::chrono::steady_clock::now());
        _animationMap["killed"] = std::make_pair([this](int id, Vector2 oldPos, Vector2 newPos) {
            if (_entities[id].crop.x == _entities[id].crop.width * 5)
                _entities.erase(id);
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }, std::chrono::steady_clock::now());
    }

    void Game::AnimateEntity(Vector2 oldPos, Vector2 newPos, int id)
    {
        const std::string& entityName = _entities[id].name;
        if (_animationMap.find(entityName) != _animationMap.end()) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - _animationMap[entityName].second).count();
            if (elapsed > 0.15f) {
                _animationMap[entityName].second = std::chrono::steady_clock::now();
                _animationMap[entityName].first(id, oldPos, newPos);
            }
        }
    }
}
