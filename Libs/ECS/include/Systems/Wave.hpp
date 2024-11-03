/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Wave
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <random>

namespace ECS {
    class Wave : public ISystem {
        public:
            void update(Coordinator& _coordinator, Entity entity);

            void handleWaves(Coordinator &_coordinator, Entity entity);

            void spawnWave(Coordinator &_coordinator, std::string &wave);

            void makeEnemySpawn(Coordinator &_coordinator, std::string &name);

            int enemiesAlive(Coordinator &_coordinator);
        protected:
        private:
            bool _started;
            std::chrono::steady_clock::time_point _clock;
            std::vector<std::string> _waveFile;
            int _idx;
            int _waveSize; // waveSize
            std::pair<int, bool> _level; // first: levelNb, second: is end of level

            void checkAndLoadWaveFile();
            void loadWave(const std::string &filename);
    };
}
