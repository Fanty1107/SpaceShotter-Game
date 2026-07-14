#include "game.hpp"

int main() {
    //TODO LATER IMPROVE GAMEOVER AND MENU SCREEN 
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");
    SetTargetFPS(FPS);

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