#include "raylib.h"
#include "game.hpp"

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");
    SetTargetFPS(60);

    
    Game game;
    game.Initialize();

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    game.Unload();
    CloseWindow();
    
    return 0;
}