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
    /**
     * @brief A struct that represents the texture of an entity.
     * 
     * This struct contains the texture of an entity. It also contains the priority of the texture.
     * The priority is used to determine the order in which the textures are drawn.
     * 
     */
    struct Images {
        Texture2D texture;
        Rectangle cropArea;
        int priority;
    };

    /**
     * @brief A struct that represents the keybinds of an entity.
     * 
     * This struct contains the keybinds of an entity. It maps keyboard keys to actions and descriptions.
     * The actions are the actions that are performed when the key is pressed. The descriptions are the
     * descriptions of the actions.
     * 
     */
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

    /**
     * @brief A struct that represents the life of an entity.
     * 
     * This struct contains the health and armor of an entity. The health is the amount of health
     * that the entity has. The armor is the amount of armor that the entity has.
     * 
     */
    struct Life {
        float health;
        float armor;
    };

    /**
     * @brief A struct that represents the power of an entity.
     * 
     * This struct contains the damage and amplifier of an entity. The damage is the amount of damage
     * that the entity can deal. The amplifier is the amount by which the damage is amplified.
     * 
     */
    struct Power {
        float damage;
        float amplifier;
    };

    /**
     * @brief A struct that represents the sounds of an entity.
     * 
     * This struct contains the sound, volume, and description of an entity. The sound is the sound
     * that the entity makes. The volume is the volume of the sound. The description is the description
     * of the sound.
     * 
     */
    struct Sounds {
        Sound sound;
        float volume;
        std::string desc;
    };

    /**
     * @brief A struct that represents the spacial properties of an entity.
     * 
     * This struct contains the position and scale of an entity. The position is the position of the
     * entity in the game world. The scale is the scale of the entity.
     * 
     */
    struct Spacial {
        Vector2 position;
        Vector2 scale;
    };

    /**
     * @brief A struct that represents the speed of an entity.
     * 
     * This struct contains the velocity and acceleration of an entity. The velocity is the velocity
     * of the entity. The acceleration is the acceleration of the entity.
     * 
     */
    struct Speed {
        float velocity;
        float acceleration;
    };

    /**
     * @brief A struct that represents the action of an entity.
     * 
     * This struct contains the type of action that the entity is performing.
     * 
     */
    struct Action {
        std::string type;
    };

    /**
     * @brief A struct that represents the entity types.
     * 
     * This struct contains the type of the entity and whether the entity is a player or not.
     * 
     */
    struct EntityTypes {
        std::string type;
        bool isPlayer;
    };
}
