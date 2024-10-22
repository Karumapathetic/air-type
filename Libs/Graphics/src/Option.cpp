/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Option
*/

#include "Option.hpp"
#include <raylib.h>

namespace Graphics {
    Option::Option(Graphics::Game& game) : _selected("Controls"),
                        _changing(""),
                        _game(game),
                        _BindedKeys({{KEY_UP, [this] { KeyUp(); }},
                                     {KEY_DOWN, [this] { KeyDown(); }},
                                     {KEY_LEFT, [this] { KeyLeft(); }},
                                     {KEY_RIGHT, [this] { KeyRight(); }},
                                     {KEY_SPACE, [this] { KeyShoot(); }},
                                     {KEY_ESCAPE, [this] { KeyEscape(); }}}),
                        _keybinds({{"Up", {KEY_UP, "Move up"}},
                                   {"Down", {KEY_DOWN, "Move down"}},
                                   {"Left", {KEY_LEFT, "Move left"}},
                                   {"Right", {KEY_RIGHT, "Move right"}},
                                   {"Shoot", {KEY_SPACE, "Shoot"}},
                                   {"Pause", {KEY_ESCAPE, "Pause/Unpause"}}}) { }

    void Option::DrawVideoSettings() {
        std::vector<std::string> options = {"Resolution", "FPS max", "Display FPS"};
        for (int i = 0; i < options.size(); i++) {
            _game.getGraphics()->RenderRoundedRectangleSides({50, (float)200 + i * 60, (float)_game.getGraphics()->GetWindowWidth() - 100, 50}, 0.2, 10, GRAY);
            _game.getGraphics()->RenderText(options[i].c_str(), 60, 215 + i * 60, 20, WHITE);
        }

        Rectangle rec = {((float)_game.getGraphics()->GetWindowWidth() / 6), (float)205, (float)_game.getGraphics()->GetWindowWidth() / 7, 40};

        std::vector<std::pair<int, int>> resolutions = {{800, 600}, {1024, 768}, {1280, 720}, {1920, 1080}};
        for (int i = 0; i < resolutions.size(); i++) {
            std::string resolutionText = std::to_string(resolutions[i].first) + "x" + std::to_string(resolutions[i].second);
            _game.getGraphics()->RenderText(resolutionText.c_str(), (_game.getGraphics()->GetWindowWidth() / 6 + i * (_game.getGraphics()->GetWindowWidth() / 7 + 15)) + _game.getGraphics()->GetWindowWidth() / 7 / 2 - _game.getGraphics()->TextSize(resolutionText.c_str(), 20) / 2, 215, 20, WHITE);
            if (_game.getGraphics()->CheckCollisionMouse(_game.getGraphics()->GetCursorPosition(), rec)) {
                _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, LIGHTGRAY);
                if (_game.getGraphics()->IsMouseButtonClicked(MOUSE_LEFT_BUTTON)) {
                    _game.getGraphics()->SetWindowResolution(resolutions[i].first, resolutions[i].second);
                }
            } else {
                _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, GRAY);
            }
            rec.x += _game.getGraphics()->GetWindowWidth() / 7 + 15;
        }

        rec.y += 60;
        rec.x = (float)_game.getGraphics()->GetWindowWidth() / 6;
        std::vector<int> fpsList = {30, 60, 120, 144};
        for (int i = 0; i < fpsList.size(); i++) {
            std::string fps = std::to_string(fpsList[i]);
            _game.getGraphics()->RenderText(fps.c_str(), (_game.getGraphics()->GetWindowWidth() / 6 + i * (_game.getGraphics()->GetWindowWidth() / 7 + 15)) + _game.getGraphics()->GetWindowWidth() / 7 / 2 - _game.getGraphics()->TextSize(fps.c_str(), 20) / 2, 275, 20, WHITE);
            if (_game.getGraphics()->CheckCollisionMouse(_game.getGraphics()->GetCursorPosition(), rec)) {
                _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, LIGHTGRAY);
                if (_game.getGraphics()->IsMouseButtonClicked(MOUSE_LEFT_BUTTON)) {
                    _game.getGraphics()->SetFPS(fpsList[i]);
                }
            } else {
                _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, GRAY);
            }
            rec.x += _game.getGraphics()->GetWindowWidth() / 7 + 15;
        }

        if (_displayfps) {
            _game.getGraphics()->RenderText("x", (_game.getGraphics()->GetWindowWidth() / 6 + 4 * (_game.getGraphics()->GetWindowWidth() / 7 + 15)) + _game.getGraphics()->GetWindowWidth() / 7 / 2 - _game.getGraphics()->TextSize("x", 20) / 2, 335, 20, WHITE);
        }
        rec.y += 60;
        if (_game.getGraphics()->CheckCollisionMouse(_game.getGraphics()->GetCursorPosition(), rec)) {
            _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, LIGHTGRAY);
            if (_game.getGraphics()->IsMouseButtonClicked(MOUSE_LEFT_BUTTON)) {
                _displayfps = !_displayfps;
            }
        } else {
            _game.getGraphics()->RenderRoundedRectangleSides(rec, 0.2, 10, GRAY);
        }
    }

    void Option::DrawControlsSettings() {
        auto keyHandlers = _BindedKeys;
        int i = 0;

        _game.getGraphics()->RenderText("Click on a key name (rectangle) to change its keybind", GetScreenWidth() / 2 - _game.getGraphics()->TextSize("Click on a key name (rectangle) to change its keybind", 20) / 2, 160, 20, WHITE);
        for (const auto& keybind : _keybinds) {
            int key = keybind.second.first;
            std::string action = "Action : " + keybind.first;
            std::string keyName = "Key : " + std::to_string(key);

            _game.getGraphics()->RenderRoundedRectangleSides({50, (float)200 + i * 60, (float)GetScreenWidth() - 100, 50}, 0.2, 10, GRAY);
            _game.getGraphics()->RenderText(action.c_str(), 60, 215 + i * 60, 20, WHITE);
            _game.getGraphics()->RenderText(keyName.c_str(), (float)GetScreenWidth() - 240, 215 + i * 60, 20, WHITE);
            if (_game.getGraphics()->CheckCollisionMouse(_game.getGraphics()->GetCursorPosition(), {(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30})) {
                _game.getGraphics()->RenderRoundedRectangleSides({(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30}, 0.2, 10, LIGHTGRAY);
                if (_game.getGraphics()->IsMouseButtonClicked(MOUSE_LEFT_BUTTON)) {
                    _changing = keybind.first;
                }
            } else {
                _game.getGraphics()->RenderRoundedRectangleSides({(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30}, 0.2, 10, GRAY);
            }
            i++;
        }
    }

    void Option::DrawSettingsOptions() {
        if (_selected == "Video") {
            DrawVideoSettings();
        } else if (_selected == "Audio") {
            _game.getGraphics()->RenderText("Coming soon...", 50, 200, 20, WHITE);
        } else if (_selected == "Controls") {
            DrawControlsSettings();
        }
        if (_changing != "") {
            _game.getGraphics()->RenderRectangle(0, 0, _game.getGraphics()->GetWindowWidth(), _game.getGraphics()->GetWindowHeight(), _game.getGraphics()->FadeColor(BLACK, 0.5));
            _game.getGraphics()->RenderText("Press a key to bind", GetScreenWidth() / 2 - _game.getGraphics()->TextSize("Press a key to bind", 20) / 2, _game.getGraphics()->GetWindowHeight() / 2, 20, WHITE);
        }
    }
} // namespace Graphics
