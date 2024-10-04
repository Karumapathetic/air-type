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
        std::vector<std::string> options = {"Resume", "Settings", "Quit"};
        for (int i = 0; i < options.size(); i++) {
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
                        break;
                    case 2:
                        _gameState = GameState::QUIT;
                        break;
                    default:
                        break;
                }
            }
            rec_option.y += GetScreenHeight() / 20 + 25;
        }
    }
}
