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
                        _Keybinds({{"Up", KEY_UP},
                                   {"Down", KEY_DOWN},
                                   {"Left", KEY_LEFT},
                                   {"Right", KEY_RIGHT},
                                   {"Shoot", KEY_SPACE},
                                   {"Escape", KEY_ESCAPE}}),
                        _BindedKeys({{KEY_UP, [this] { KeyUp(); }},
                                     {KEY_DOWN, [this] { KeyDown(); }},
                                     {KEY_LEFT, [this] { KeyLeft(); }},
                                     {KEY_RIGHT, [this] { KeyRight(); }},
                                     {KEY_SPACE, [this] { KeyShoot(); }},
                                     {KEY_ESCAPE, [this] { KeyEscape(); }}}) { }

    void Option::DrawControls() {
        auto keyHandlers = _BindedKeys;
        int i = 0;

        DrawText("Click on a key name (rectangle) to change its keybind", GetScreenWidth() / 2 - MeasureText("Click on a key name (rectangle) to change its keybind", 20) / 2, 160, 20, WHITE);
        for (const auto& keybind : _Keybinds) {
            int key = keybind.second;
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
        if (_selected == "General") {
            DrawText("Coming soon...", 50, 100, 20, WHITE);
        } else if (_selected == "Video") {
            DrawText("Coming soon...", 50, 100, 20, WHITE);
        } else if (_selected == "Audio") {
            DrawText("Coming soon...", 50, 100, 20, WHITE);
        } else if (_selected == "Controls") {
            DrawControls();
        }
        if (_changing != "") {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.5));
            DrawText("Press a key to bind", GetScreenWidth() / 2 - MeasureText("Press a key to bind", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
        }
    }
} // namespace Graphics
