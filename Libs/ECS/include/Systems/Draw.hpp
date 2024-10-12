/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Draw
*/

#pragma once

#include "ISystem.hpp"

    namespace ECS {
        /**
         * @brief System that handles the drawing of entities.
         */
        class Draw : public ISystem {
            public:
                void RenderEntitiesWithImages(std::string image, Rectangle cropArea, Vector2 position, Vector2 scale) {
                }
            protected:
            private:
        };
}
