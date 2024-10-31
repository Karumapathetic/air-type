/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawSettings
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawRectangleBackground() const {
        Rectangle rec = {
            25,
            25,
            (float)_graphics->GetWindowWidth() - 50,
            (float)_graphics->GetWindowHeight() - 50
        };
        _graphics->RenderRoundedRectangle(rec, 0.2, 10, BLACK);
        _graphics->RenderRoundedRectangleSides(rec, 0.2, 2, GRAY);
    }

    void Game::DrawSettingsTitles() {
        int recOptionLen = _graphics->GetWindowWidth() / 10;
        Rectangle rec_option = {
            (float)_graphics->GetWindowWidth() / 2 - recOptionLen * 2,
            (float)_graphics->GetWindowHeight() / 10 - 30,
            (float)_graphics->GetWindowWidth() / 10,
            (float)_graphics->GetWindowHeight() / 20
        };
        _graphics->RenderText("Settings", _graphics->GetWindowWidth() / 2 - _graphics->TextSize("Settings", 25) / 2, 40, 25, WHITE);
        std::vector<std::string> options = {"Video", "Audio", "Controls"};
        for (int i = 0; i < options.size(); i++) {
            if (_graphics->CheckCollisionMouse(_graphics->GetCursorPosition(), rec_option)) {
                _graphics->RenderRoundedRectangle(rec_option, 0.2, 10, DARKGRAY);
                if (_graphics->IsMouseButtonClicked(MOUSE_LEFT_BUTTON)) {
                    _option->setSelected(options[i]);
                }
            } else {
                _graphics->RenderRoundedRectangleSides(rec_option, 0.2, 1, GRAY);
            }
            _graphics->RenderText(options[i].c_str(), rec_option.x + rec_option.width / 2 - _graphics->TextSize(options[i].c_str(), 20) / 2, rec_option.y + 5, 20, WHITE);
            rec_option.x += recOptionLen;
        }
    }

    void Game::DrawSettings() {
        DrawStars();
        DrawRectangleBackground();
        DrawSettingsTitles();
        _option->DrawSettingsOptions();
    }
} // namespace Graphics
