#include "raylib.h"


int main() {
    InitWindow(800, 450, "Setup Raylib C++ - Teste");
    SetTargetFPS(60);
   

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib configurado com sucesso!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}