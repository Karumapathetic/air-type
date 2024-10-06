/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawPause
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawPause() {
        Rectangle rec_option = {
            (float)GetScreenWidth() / 2 - 100,
            (float)GetScreenHeight() / 3,
            (float)GetScreenWidth() / 10,
            (float)GetScreenHeight() / 20
        };
        DrawStars();
        DrawText("Pause", GetScreenWidth() / 2 - MeasureText("Pause", 40) / 2, GetScreenHeight() / 4, 40, WHITE);
        std::vector<std::string> options = {"Resume", "Settings", "Quit"};
        bool hovering = false;
        for (int i = 0; i < options.size(); i++) {
            if (_option->getSelected() == options[i])
                DrawRectangleRounded(rec_option, 0.3, 0, DARKGRAY);
            else
                DrawRectangleRounded(rec_option, 0.3, 0, BLACK);
            DrawRectangleRoundedLines(rec_option, 0.3, 2, GRAY);
            DrawText(options[i].c_str(), GetScreenWidth() / 2 - MeasureText(options[i].c_str(), 25) / 2, rec_option.y + 15, 25, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), rec_option) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                switch (i) {
                    case 0:
                        _gameState = GameState::GAME;
                        break;
                    case 1:
                        _gameState = GameState::SETTINGS;
                        _option->setSelected("Controls");
                        return;
                    case 2:
                        _gameState = GameState::QUIT;
                        break;
                    default:
                        break;
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), rec_option)) {
                _option->setSelected(options[i]);
                hovering = true;
            }
            rec_option.y += GetScreenHeight() / 20 + 25;
        }
        if (!hovering)
            _option->setSelected("");
    }
}
