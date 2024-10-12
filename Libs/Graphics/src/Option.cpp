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
            DrawRectangleRoundedLines({50, (float)200 + i * 60, (float)GetScreenWidth() - 100, 50}, 0.2, 10, GRAY);
            DrawText(options[i].c_str(), 60, 215 + i * 60, 20, WHITE);
        }

        std::vector<std::pair<int, int>> resolutions = {{800, 600}, {1024, 768}, {1280, 720}, {1920, 1080}};
        for (int i = 0; i < resolutions.size(); i++) {
            std::string resolutionText = std::to_string(resolutions[i].first) + "x" + std::to_string(resolutions[i].second);
            DrawText(resolutionText.c_str(), (GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15)) + GetScreenWidth() / 7 / 2 - MeasureText(resolutionText.c_str(), 20) / 2, 215, 20, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), {(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)205, (float)GetScreenWidth() / 7, 40})) {
                DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)205, (float)GetScreenWidth() / 7, 40}, 0.2, 10, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    SetWindowSize(resolutions[i].first, resolutions[i].second);
                }
            } else {
                DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)205, (float)GetScreenWidth() / 7, 40}, 0.2, 10, GRAY);
            }
        }

        std::vector<int> fpsList = {30, 60, 120, 144};
        for (int i = 0; i < fpsList.size(); i++) {
            std::string fps = std::to_string(fpsList[i]);
            DrawText(fps.c_str(), (GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15)) + GetScreenWidth() / 7 / 2 - MeasureText(fps.c_str(), 20) / 2, 275, 20, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), {(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)265, (float)GetScreenWidth() / 7, 40})) {
                DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)265, (float)GetScreenWidth() / 7, 40}, 0.2, 10, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    SetTargetFPS(fpsList[i]);
                }
            } else {
                DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + i * (GetScreenWidth() / 7 + 15), (float)265, (float)GetScreenWidth() / 7, 40}, 0.2, 10, GRAY);
            }
        }

        if (_displayfps) {
            DrawText("x", (GetScreenWidth() / 6 + 4 * (GetScreenWidth() / 7 + 15)) + GetScreenWidth() / 7 / 2 - MeasureText("x", 20) / 2, 335, 20, WHITE);
        }
        if (CheckCollisionPointRec(GetMousePosition(), {(float)GetScreenWidth() / 6 + 4 * (GetScreenWidth() / 7 + 15), (float)325, (float)GetScreenWidth() / 7, 40})) {
            DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + 4 * (GetScreenWidth() / 7 + 15), (float)325, (float)GetScreenWidth() / 7, 40}, 0.2, 10, LIGHTGRAY);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                _displayfps = !_displayfps;
            }
        } else {
            DrawRectangleRoundedLines({(float)GetScreenWidth() / 6 + 4 * (GetScreenWidth() / 7 + 15), (float)325, (float)GetScreenWidth() / 7, 40}, 0.2, 10, GRAY);
        }
    }

    void Option::DrawControlsSettings() {
        auto keyHandlers = _BindedKeys;
        int i = 0;

        DrawText("Click on a key name (rectangle) to change its keybind", GetScreenWidth() / 2 - MeasureText("Click on a key name (rectangle) to change its keybind", 20) / 2, 160, 20, WHITE);
        for (const auto& keybind : _keybinds) {
            int key = keybind.second.first;
            std::string action = "Action : " + keybind.first;
            std::string keyName = "Key : " + std::to_string(key);

            DrawRectangleRoundedLines({50, (float)200 + i * 60, (float)GetScreenWidth() - 100, 50}, 0.2, 10, GRAY);
            DrawText(action.c_str(), 60, 215 + i * 60, 20, WHITE);
            DrawText(keyName.c_str(), (float)GetScreenWidth() - 240, 215 + i * 60, 20, WHITE);
            if (CheckCollisionPointRec(GetMousePosition(), {(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30})) {
                DrawRectangleRoundedLines({(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30}, 0.2, 10, LIGHTGRAY);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    _changing = keybind.first;
                }
            } else {
                DrawRectangleRoundedLines({(float)GetScreenWidth() - 250, (float)210 + i * 60, 150, 30}, 0.2, 10, GRAY);
            }
            i++;
        }
    }

    void Option::DrawSettingsOptions() {
        if (_selected == "Video") {
            DrawVideoSettings();
        } else if (_selected == "Audio") {
            DrawText("Coming soon...", 50, 200, 20, WHITE);
        } else if (_selected == "Controls") {
            DrawControlsSettings();
        }
        if (_changing != "") {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5));
            DrawText("Press a key to bind", GetScreenWidth() / 2 - MeasureText("Press a key to bind", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
        }
    }
} // namespace Graphics
