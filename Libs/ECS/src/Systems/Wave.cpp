/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Wave
*/

#include "Wave.hpp"

namespace ECS {
    void Wave::update(Coordinator &_coordinator, Entity entity) {
        handleWaves(_coordinator, entity);
    }

    void Wave::makeEnemySpawn(Coordinator &_coordinator, std::string &name) {
        Entity entity = _coordinator.createEntity(name);
        _coordinator.initEntities();
        auto &entityPos = _coordinator.getComponent<Spacial>(entity);
        int random = rand() % 400;
        entityPos.position.x = MAX_X - random;
        entityPos.position.y = rand() % (MAX_Y - 400) + 200;
    }

    void Wave::spawnWave(Coordinator &_coordinator, std::string &wave) {
        std::istringstream waveStream(wave);
        std::string enemyDefinition;
        while (std::getline(waveStream, enemyDefinition, ',')) {
            std::istringstream enemyStream(enemyDefinition);
            std::string enemyName;
            int enemyCount;
            enemyStream >> enemyName >> enemyCount;
            _waveSize += enemyCount;
            for (int i = 0; i < enemyCount; ++i) {
                makeEnemySpawn(_coordinator, enemyName);
            }
        }
    }

    void Wave::handleWaves(Coordinator &_coordinator, Entity entity) {
        if (_coordinator.getGameStarted() && !_started) {
            _started = true;
            _clock = std::chrono::steady_clock::now();
            _idx = 0;
            _level = std::make_pair(1, false);
            _waveSize = 0;
            checkAndLoadWaveFile();
        }
        if (_started) {
            int alive = enemiesAlive(_coordinator);
            auto now = std::chrono::steady_clock::now();
            if (alive > _waveSize / 2)
                _clock = now;
            _waveSize = alive;
            auto elapsed = std::chrono::duration<float>(now - _clock).count();
            if (elapsed >= 5.0f) {
                _clock = now;
                spawnWave(_coordinator, _waveFile[_idx]);
                _idx++;
            }
        }
    }

    int Wave::enemiesAlive(Coordinator &_coordinator) {
        int alive = 0;
        ComponentType type = _coordinator.getComponentType<EntityTypes>();
        const auto &entities = _coordinator.getEntities();
        for (const auto &entity : entities) {
            if (!_coordinator.hasComponent(entity, type)) continue;
            auto &entityType = _coordinator.getComponent<EntityTypes>(entity);
            if (entityType.type == "enemy")
                alive++;
        }
        return alive;
    }

    void Wave::checkAndLoadWaveFile() {
        std::string nameToFind = "level." + std::to_string(_level.first);
        std::filesystem::path wavesDir("Waves");
        if (!std::filesystem::exists(wavesDir) || std::filesystem::is_empty(wavesDir)) {
            throw std::runtime_error("Waves directory is empty or does not exist.");
        }

        for (const auto& entry : std::filesystem::directory_iterator(wavesDir)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                if (filename == nameToFind) {
                    loadWave(entry.path().string());
                    return;
                }
            }
        }
        throw std::runtime_error("No wave file found in the waves directory.");
    }

    void Wave::loadWave(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::string line;
        while (std::getline(file, line)) {
            _waveFile.push_back(line);
        }
        file.close();
    }
}
