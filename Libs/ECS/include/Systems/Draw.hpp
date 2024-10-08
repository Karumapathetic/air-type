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
                void RenderEntitiesWithImages(Texture2D image, Rectangle cropArea, Vector2 position, Vector2 scale) {
                    if (image.id != 0) {
                        Rectangle destinationRectangle = {position.x, position.y, scale.x, scale.y};
                        DrawTexturePro(image, cropArea, destinationRectangle, {0.0f, 0.0f}, 0.0f, WHITE);
                    }
                }
            protected:
            private:
        };
}
