/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Wave
*/

#pragma once

#include "ISystem.hpp"
#include "Coordinator.hpp"
#include "fstream"
#include "sstream"

namespace ECS {
    class Wave : public ISystem {
        public:
            void update(Coordinator& _coordinator, Entity entity);

            void handleWaves(Coordinator &_coordinator, Entity entity);
        protected:
        private:
            bool _started;
            std::chrono::steady_clock::time_point _clock;
            std::vector<std::string> _waveFile;
            int _idx;

            void loadFile(const std::string &filename);
    };
}
