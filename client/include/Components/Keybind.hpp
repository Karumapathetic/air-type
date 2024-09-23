/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Keybind
*/

#pragma once

#include "IComponent.hpp"

class Keybind : public IComponent {
    public:
        Keybind();
        ~Keybind();

        getKey() { return key; }
        getDesc() { return desc; }
        getAction() { return action; }
        setKey(int key) { this->key = key; }
        setDesc(std::string desc) { this->desc = desc; }
        setAction(std::string action) { this->action = action; }
    protected:
    private:
        std::string desc;
        int key;
        std::string action;
};
