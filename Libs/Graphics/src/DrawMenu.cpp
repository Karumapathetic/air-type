/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** DrawMenu
*/

#include "Game.hpp"

namespace Graphics {
    void Game::DrawMenu() {
        // DrawText("Menu", 400, 200, 20, GRAY);
        int framesCounter = 0;
        SetTargetFPS(60);
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        Vector2 mousePoint = GetMousePosition();
        ClearBackground(BLACK);
        DrawText("Menu", 400, 100, 20, GRAY);
        // Join button
        Rectangle joinButton = DrawButton("Join", 400, 200, screenWidth, screenHeight, DARKGRAY, GRAY, {0.5, 0.2});
        if (CheckCollisionPointRec(mousePoint, joinButton)) {
            DrawButton("Join", 400, 200, screenWidth, screenHeight, RED, WHITE, {0.5, 0.2});
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                setGameState(GameState::GAME);
            }
        }

        // Host button
        Rectangle hostButton = DrawButton("Host", 400, 300, screenWidth, screenHeight, DARKGRAY, GRAY, {0.5, 0.3});
        if (CheckCollisionPointRec(mousePoint, hostButton)) {
            DrawButton("Host", 400, 300, screenWidth, screenHeight, RED, WHITE, {0.5, 0.3});
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                setGameState(GameState::GAME);
            }
        }

        // Settings button
        Rectangle settingsButton = DrawButton("Settings", 400, 400, screenWidth, screenHeight, DARKGRAY, GRAY, {0.5, 0.4});
        if (CheckCollisionPointRec(mousePoint, settingsButton)) {
            DrawButton("Settings", 400, 400, screenWidth, screenHeight, RED, WHITE, {0.5, 0.4});
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                setGameState(GameState::SETTINGS);
            }
        }

        // Exit button
        Rectangle exitButton = DrawButton("Exit", 400, 500, screenWidth, screenHeight, DARKGRAY, GRAY, {0.5, 0.5});
        if (CheckCollisionPointRec(mousePoint, exitButton)) {
            DrawButton("Exit", 400, 500, screenWidth, screenHeight, RED, WHITE, {0.5, 0.5});
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                CloseWindow();
            }
        }
    }

    Vector2 Game::Center(Vector2 objectSize, Vector2 screenSize, Vector2 percentage) {
        Vector2 position;
        position.x = screenSize.x * percentage.x - objectSize.x / 2;
        position.y = screenSize.y * percentage.y - objectSize.y / 2;
        return position;
    }

    Rectangle Game::DrawButton(const char *text, int x, int y, int width, int height, Color color, Color textColor, Vector2 percentage) {
        Vector2 buttonSize = {300, 100};
        Vector2 centeredPosition = Center(buttonSize, {static_cast<float>(width), static_cast<float>(height)}, percentage);
        int textWidth = MeasureText(text, 50);
        int textHeight = 50;
        Vector2 buttonCenter = {centeredPosition.x + (buttonSize.x - textWidth) / 2, centeredPosition.y + (buttonSize.y - textHeight) / 2};

        DrawRectangle(centeredPosition.x, centeredPosition.y, buttonSize.x, buttonSize.y, color);
        DrawText(text, buttonCenter.x, buttonCenter.y, 50, textColor);
        return {centeredPosition.x, centeredPosition.y, buttonSize.x, buttonSize.y};
    }
} // namespace Graphics