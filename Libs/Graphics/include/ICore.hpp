/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** ICore
*/

#ifndef ICORE_HPP
#define ICORE_HPP

#ifdef _WIN32 // Pour Windows
    #ifdef GRAPHICS_EXPORTS
        #define GRAPHICS_API __declspec(dllexport)
    #else
        #define GRAPHICS_API __declspec(dllimport)
    #endif
#else // Pour Linux ou d'autres systèmes
    #define GRAPHICS_API __attribute__((visibility("default")))
#endif

#include <memory>

#include "IGame.hpp"

namespace Graphics {
    class ICore {
    public:
        virtual ~ICore() = default;

        virtual void InitGame() = 0;
        virtual void InitStars(int numStars) = 0;
        virtual void Caillou(bool *isRunning) = 0;
    };

    extern "C" GRAPHICS_API ICore* CreateGraphics();
    extern "C" GRAPHICS_API void DestroyGraphics(ICore* graphics);
}

#endif // ICORE_HPP
