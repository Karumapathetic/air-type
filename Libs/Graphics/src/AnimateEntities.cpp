/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** AnimateEntities
*/

#include "Game.hpp"

namespace Graphics {
    void Game::AnimationsMap(int id, Vector2 oldPos, Vector2 newPos) {
        std::string name = _entities[id].name;
        if (name == "player") {
            if (oldPos.y > newPos.y) {
                if (_entities[id].crop.x == _entities[id].crop.width * 4)
                    return;
                _entities[id].crop.x += _entities[id].crop.width;
            } else if (oldPos.y < newPos.y) {
                if (_entities[id].crop.x == 0)
                    return;
                _entities[id].crop.x -= _entities[id].crop.width;
            }
        } else if (name == "pata-pata") {
            if (_entities[id].crop.x == _entities[id].crop.width * 7)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        } else if (name == "win") {
            if (_entities[id].crop.x == _entities[id].crop.width * 2)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        } else if (name == "wick") {
            if (_entities[id].crop.x == _entities[id].crop.width * 3)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        } else if (name == "missile") {
            if (_entities[id].crop.x == _entities[id].crop.width)
                _entities[id].crop.x = 0;
            else
                _entities[id].crop.x += _entities[id].crop.width;
        } else if (name == "killed") {
            if (_entities[id].crop.x == _entities[id].crop.width * 5)
                DestroyEntity(id);
            else
                _entities[id].crop.x += _entities[id].crop.width;
        }
    }

    void Game::AnimateEntity(Vector2 oldPos, Vector2 newPos, int id)
    {
        if (_animationMap.find(id) != _animationMap.end()) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - _animationMap[id]).count();
            if (elapsed > 0.15f) {
                _animationMap[id] = now;
                AnimationsMap(id, oldPos, newPos);
            }
        }
    }
}
