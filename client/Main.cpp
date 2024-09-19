#include <iostream>
#include "raylib.h"

int main() {

    InitWindow(800, 600, "R-Type");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Lezgong", 190, 200, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();

    std::cout << "Hello client" << std::endl;
    return 0;
}
