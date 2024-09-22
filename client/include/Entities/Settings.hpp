/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Settings
*/

#pragma once

#include "IEntity.hpp"

// Components
#include "Keybind.hpp"
#include "Sound.hpp"

class Settings : public IEntity {
    public:
        Settings();
        ~Settings();
    protected:
    private:
        Keybind *_keybind;
        Sound *_sound;
};
