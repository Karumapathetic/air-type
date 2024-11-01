/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Components
*/

#pragma once

#include <string>
#include <chrono>
#include <unordered_map>

#include "PathingStrategy.hpp"

namespace ECS {
    /**
     * @brief A struct that represents a 2D vector.
     * 
     * This struct contains the x and y coordinates of a 2D vector.
     * 
     */
    struct Vector2 {
        float x;
        float y;
    };

    /**
     * @brief A struct that represents the texture of an entity.
     * 
     * This struct contains the texture of an entity.
     * 
     */
    struct Images {
        std::string texture;
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
        std::unordered_map<std::string, std::pair<int, std::string>> keybinds;

        Keybind() = default;
        Keybind(int key, const std::string &action, const std::string &desc) {
            keybinds[action] = std::make_pair(key, desc);
        }
        void addKeybind(int key, const std::string &action, const std::string &desc) {
            keybinds[action] = std::make_pair(key, desc);
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
     * @brief A struct that represents the spacial properties of an entity.
     * 
     * This struct contains the position and scale of an entity. The position is the position of the
     * entity in the game world. The scale is the scale of the entity.
     * 
     */
    struct Spacial {
        Vector2 position;
        Vector2 size;
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
        bool vertically;
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
        int id;
    };

    /**
     * @brief A struct that handles various types of cooldowns.
     * 
     * This struct contains maps of cooldown times and last activation times for each type of cooldown.
     * 
     */
    struct Cooldown {
        std::unordered_map<std::string, float> cooldowns; // <type, cooldown time>
        std::unordered_map<std::string,std::pair<float, std::chrono::steady_clock::time_point>> activation; // pair:<number of times it needs to be activated, timer since last activation>

        Cooldown() = default;

        void addCooldown(const std::string &type, float cooldownTime, float activationTimes) {
            cooldowns[type] = cooldownTime;
            activation[type].first = activationTimes;
            activation[type].second = std::chrono::steady_clock::now();
        }

        float getRemainingCooldown(const std::string &type) const {
            auto it = activation.find(type);
            if (it != activation.end()) {
                auto now = std::chrono::steady_clock::now();
                float elapsed = std::chrono::duration<float>(now - it->second.second).count();
                return cooldowns.at(type) - elapsed;
            }
            return 0.0f;
        }
    };

    /**
     * @brief A struct that handles the pathing of an enemy
     * 
     * Handles all his changes of positions
     * 
     */
    struct Pathing {
        std::shared_ptr<PathingStrategy> pathing;
    };
}
