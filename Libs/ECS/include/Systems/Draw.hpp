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
                void RenderEntitiesWithImages(Texture2D image) {
                    if (image.id != 0) {
                        // Dessiner l'image en utilisant Raylib
                        DrawTexture(image, 100, 100, WHITE);
                    }
                }
            protected:
            private:
        };
}
