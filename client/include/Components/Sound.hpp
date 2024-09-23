/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Sound
*/

#pragma once

#include "IComponent.hpp"

class Sound : public IComponent {
    public:
        Sound();
        ~Sound();

        getVolume() { return volume; }
        getDesc() { return desc; }
        setVolume(float volume) { this->volume = volume; }
        setDesc(std::string desc) { this->desc = desc; }
    protected:
    private:
        float volume;
        std::string desc;
};
