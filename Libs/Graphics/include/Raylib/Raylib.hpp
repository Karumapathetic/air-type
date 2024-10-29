/*
** EPITECH PROJECT, 2024
** air-type
** File description:
** Raylib
*/

#pragma once

#include <unordered_map>
#include <raylib.h>

#include "IGraphic.hpp"

namespace Graphics {
    class RaylibGraphics : public IGraphic {
        public:
            ~RaylibGraphics() {
                for (auto &texture : _textures) {
                    UnloadTexture(texture.second);
                }
                _textures.clear();
            };

            void InitGraphics(const char *title) override {
                int screenWidth = GetScreenWidth();
                int screenHeight = GetScreenHeight();
                InitWindow(screenWidth, screenHeight, title);
                ToggleFullscreen();
                InitAudioDevice();
                SetExitKey(KEY_BACKSPACE);
            }

            void CloseGraphics() override {
                CloseWindow();
                CloseAudioDevice();
            }

            int GetWindowWidth() override {
                return GetScreenWidth();
            }

            int GetWindowHeight() override {
                return GetScreenHeight();
            }

            void RenderCircle(int x, int y, int radius, Color color) override {
                DrawCircle(x, y, radius, {color.r, color.g, color.b, color.a});
            }

            void RenderRectangle(int posX, int posY, int width, int height, Color color) override {
                DrawRectangle(posX, posY, width, height, {color.r, color.g, color.b, color.a});
            }

            void RenderRoundedRectangle(Rectangle rec, float roundness, int segments, Color color) override {
                DrawRectangleRounded({rec.x, rec.y, rec.width, rec.height}, roundness, segments, {color.r, color.g, color.b, color.a});
            }

            void RenderRoundedRectangleSides(Rectangle rec, float roundness, int segments, Color color) override {
                DrawRectangleRoundedLines({rec.x, rec.y, rec.width, rec.height}, roundness, segments, {color.r, color.g, color.b, color.a});
            }

            void RenderText(const char *text, int posX, int posY, int fontSize, Color color) override {
                DrawText(text, posX, posY, fontSize, {color.r, color.g, color.b, color.a});
            }

            int TextSize(const char *text, int fontSize) override {
                return MeasureText(text, fontSize);
            }

            Vector2 GetCursorPosition() override {
                ::Vector2 pos = GetMousePosition();
                return {pos.x, pos.y};
            }

            bool CheckCollisionMouse(Vector2 point, Rectangle rec) override {
                return CheckCollisionPointRec({point.x, point.y}, {rec.x, rec.y, rec.width, rec.height});
            }

            bool IsMouseButtonClicked(int button) override {
                return IsMouseButtonPressed(button);
            }

            void RenderPreciseTexture(int Id, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint) override {
                DrawTexturePro(_textures[Id], {source.x, source.y, source.width, source.height}, {dest.x, dest.y, dest.width, dest.height}, {origin.x, origin.y}, rotation, {tint.r, tint.g, tint.b, tint.a});
            }

            void RenderFPS(int posX, int posY) override {
                DrawFPS(10, 10);
            }

            void StartRendering() override {
                BeginDrawing();
            }

            void EndRendering() override {
                EndDrawing();
            }

            void ResetBackground(Color color) override {
                ClearBackground({color.r, color.g, color.b, color.a});
            }

            bool IsInputPressed(int key) override {
                return IsKeyDown(key);
            }

            void SetWindowResolution(int width, int height) override {
                SetWindowSize(width, height);
            }

            void SetFPS(int fps) override {
                SetTargetFPS(fps);
            }

            Color FadeColor(Color color, float alpha) override {
                ::Color fadedColor = Fade({color.r, color.g, color.b, color.a}, alpha);
                return {fadedColor.r, fadedColor.g, fadedColor.b, fadedColor.a};
            }

            bool IsWindowClosing() override {
                return WindowShouldClose();
            }

            void LoadTextureFromFile(int Id, const char *filename) override {
                _textures[Id] = LoadTexture(filename);
            }

            void UnloadTextureById(int Id) override {
                if (_textures.find(Id) != _textures.end()) {
                    UnloadTexture(_textures[Id]);
                    _textures.erase(Id);
                }
            }
        protected:
        private:
            std::unordered_map<int, ::Texture2D> _textures;
    };
}
