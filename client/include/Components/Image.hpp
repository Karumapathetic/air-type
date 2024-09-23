/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Image
*/

#pragma once

#include "raylib.h"

#include "IComponent.hpp"

class Image : public IComponent {
    public:
        Image(Texture2D texture) : texture(texture) {
            texture = LoadTexture(texture);
        };
        ~Image() {
            UnloadTexture(texture);
        };

        getTexture() { return texture; }
        getPriority() { return priority; }
        setTexture(Texture2D texture) { this->texture = texture; }
        setPriority(float priority) { this->priority = priority; }
    protected:
    private:
        Texture2D texture;
        float priority;
};
