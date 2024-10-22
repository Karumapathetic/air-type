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
            (float)_graphics->GetWindowWidth() / 2 - 100,
            (float)_graphics->GetWindowHeight() / 3,
            (float)_graphics->GetWindowWidth() / 10,
            (float)_graphics->GetWindowHeight() / 20
        };
        DrawStars();
        _graphics->RenderText("Pause", _graphics->GetWindowWidth() / 2 - _graphics->TextSize("Pause", 40) / 2, _graphics->GetWindowHeight() / 4, 40, WHITE);
        std::vector<std::string> options = {"Resume", "Settings", "Quit"};
        bool hovering = false;
        for (int i = 0; i < options.size(); i++) {
            if (_option->getSelected() == options[i])
                _graphics->RenderRoundedRectangle(rec_option, 0.3, 0, DARKGRAY);
            else
                _graphics->RenderRoundedRectangle(rec_option, 0.3, 0, BLACK);
            _graphics->RenderRoundedRectangleSides(rec_option, 0.3, 2, GRAY);
            _graphics->RenderText(options[i].c_str(), _graphics->GetWindowWidth() / 2 - _graphics->TextSize(options[i].c_str(), 25) / 2, rec_option.y + 15, 25, WHITE);
            if (_graphics->CheckCollisionMouse(_graphics->GetCursorPosition(), rec_option) && _graphics->IsMouseButtonClicked(MOUSE_BUTTON_LEFT)) {
                switch (i) {
                    case 0:
                        _gameState = GameState::GAME;
                        break;
                    case 1:
                        _previousState = GameState::PAUSE;
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
            if (_graphics->CheckCollisionMouse(_graphics->GetCursorPosition(), rec_option)) {
                _option->setSelected(options[i]);
                hovering = true;
            }
            rec_option.y += _graphics->GetWindowHeight() / 20 + 25;
        }
        if (!hovering)
            _option->setSelected("");
    }
}
