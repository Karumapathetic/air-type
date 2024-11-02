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

    void spawnWave(Coordinator &_coordinator, std::string wave) {
        std::istringstream waveStream(wave);
        std::string enemyDefinition;
        while (std::getline(waveStream, enemyDefinition, ',')) {
            std::istringstream enemyStream(enemyDefinition);
            std::string enemyName;
            int enemyCount;
            enemyStream >> enemyName >> enemyCount;
            for (int i = 0; i < enemyCount; ++i) {
                std::cout << "Creating: " << enemyName << " " << enemyCount << std::endl;
            }
        }
    }

    void Wave::handleWaves(Coordinator &_coordinator, Entity entity) {
        if (_coordinator.getGameStarted() && !_started) {
            std::cout << "Started !" << std::endl;
            loadFile("Wave/wave.level1");
            _started = true;
            _clock = std::chrono::steady_clock::now();
            _idx = 0;
        }
        if (_started) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration<float>(now - _clock).count();
            if (elapsed >= 5.0f) {
                _clock = now;
                spawnWave(_coordinator, _waveFile[_idx]);
                _idx++;
            }
        }
    }

    void Wave::loadFile(const std::string& filename) {
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
