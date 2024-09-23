/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Action
*/

#pragma once

class Action {
    public:
        Action();
        ~Action();

        getType() { return type; }
        setType(std::string type) { this->type = type; }
    protected:
    private:
        std::string type;
};
