/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ICore
*/

#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

#include "IGame.hpp"

namespace Graphics {
    class ICore {
    public:
        virtual ~ICore() = default;

        virtual void InitGame() = 0;
        virtual void InitStars(int numStars) = 0;
        virtual void Caillou(bool *isRunning) = 0;
        virtual IGame& getGame() = 0;
    };
}

#endif // ICORE_HPP
