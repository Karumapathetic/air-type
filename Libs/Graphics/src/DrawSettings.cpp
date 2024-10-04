/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawSettings
*/

#include "Game.hpp"

namespace Graphics {
    void DrawRectangleBackground() {
        Rectangle rec = {
            25,
            25,
            (float)GetScreenWidth() - 50,
            (float)GetScreenHeight() - 50
        };
        DrawRectangleRounded(rec, 0.2, 10, BLACK);
        DrawRectangleRoundedLines(rec, 0.2, 2, GRAY);
    }

    void Game::DrawSettingsTitles() {
        int recOptionLen = GetScreenWidth() / 10;
        Rectangle rec_option = {
            (float)GetScreenWidth() / 2 - recOptionLen * 2,
            (float)GetScreenHeight() / 10 - 30,
            (float)GetScreenWidth() / 10,
            (float)GetScreenHeight() / 20
        };
        DrawText("Settings", GetScreenWidth() / 2 - MeasureText("Settings", 25) / 2, 40, 25, WHITE);
        std::vector<std::string> options = {"General", "Video", "Audio", "Controls"};
        for (int i = 0; i < options.size(); i++) {
            if (CheckCollisionPointRec(GetMousePosition(), rec_option)) {
                DrawRectangleRounded(rec_option, 0.2, 10, DARKGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    _selected = options[i];
                }
            } else {
                DrawRectangleRoundedLines(rec_option, 0.2, 1, GRAY);
            }
            DrawText(options[i].c_str(), rec_option.x + rec_option.width / 2 - MeasureText(options[i].c_str(), 20) / 2, rec_option.y + 5, 20, WHITE);
            rec_option.x += recOptionLen;
        }
    }

    void Game::DrawSettings() {
        DrawStars();
        DrawRectangleBackground();
        DrawSettingsTitles();
        // if (_selected == "General") {
        //     ;
        // } else if (_selected == "Video") {
        //     ;
        // } else if (_selected == "Audio") {
        //     ;
        // } else if (_selected == "Controls") {
        //     ;
        // }
    }
} // namespace Graphics
