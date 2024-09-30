/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Components
*/

#pragma once

#include <raylib.h>
#include <string>

namespace ECS {
    struct Images {
        Texture2D texture;
        int priority;
    };

    struct Keybind {
        std::unordered_map<KeyboardKey, std::pair<std::string, std::string>> keybinds;

        Keybind() = default;
        Keybind(KeyboardKey key, const std::string &action, const std::string &desc) {
            keybinds[key] = std::make_pair(action, desc);
        }
        void addKeybind(KeyboardKey key, const std::string &action, const std::string &desc) {
            keybinds[key] = std::make_pair(action, desc);
        }
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
        Sound sound;
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
}