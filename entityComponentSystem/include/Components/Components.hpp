/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Components
*/

#pragma once

#include <raylib.h>
#include <string>

struct Images {
    Texture2D texture;
    int priority;
};

struct Keybind {
    int key;
    std::string action;
    std::string desc;
};

struct Life {
    float health;
    float armor;
};

struct Power {
    float damage;
    float amplifier;
};

struct Sounds {
    float volume;
    std::string desc;
};

struct Spacial {
    float position;
    float scale;
};

struct Speed {
    float velocity;
    float acceleration;
};

struct Action {
    std::string type;
};

struct EntityTypes {
    std::string type;
    bool isPlayer;
};