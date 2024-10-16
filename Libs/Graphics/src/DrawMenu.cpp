/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawMenu
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawMenu() {
        Rectangle rec_option = {
            (float)GetScreenWidth() / 2 - 100,
            (float)GetScreenHeight() / 3,
            (float)GetScreenWidth() / 10,
            (float)GetScreenHeight() / 20
        };
        std::vector<std::string> options = {"Play", "Settings", "Quit"};
        bool hovering = false;

        // Draw moving stars
        for (auto &star : _stars) {
            star.x -= 1.0f;
            if (star.x < 0) {
                star.x = GetScreenWidth();
                star.y = static_cast<float>(std::rand() % GetScreenHeight());
            }
        }
        DrawStars();
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
                        _previousState = GameState::MENU;
                        _gameState = GameState::SETTINGS;
                        _option->setSelected("Video");
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
    }
} // namespace Graphics
