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
            (float)_graphics->GetWindowWidth() / 2 - 100,
            (float)_graphics->GetWindowHeight() / 3,
            (float)_graphics->GetWindowWidth() / 10,
            (float)_graphics->GetWindowHeight() / 20
        };
        std::vector<std::string> options = {"Play", "Settings", "Quit"};
        bool hovering = false;

        // Draw moving stars
        for (auto &star : _stars) {
            star.x -= 1.0f;
            if (star.x < 0) {
                star.x = _graphics->GetWindowWidth();
                star.y = static_cast<float>(std::rand() % _graphics->GetWindowHeight());
            }
        }
        DrawStars();
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
                        setGameState(GameState::GAME);
                        addClientAction("start");
                        break;
                    case 1:
                        setGameState(GameState::SETTINGS);
                        _option->setSelected("Video");
                        return;
                    case 2:
                        setGameState(GameState::QUIT);
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
    }
} // namespace Graphics
