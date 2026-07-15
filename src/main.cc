#include "game.hpp"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");
    SetTargetFPS(FPS);

    Game game;
    game.Initialize();

    while (!WindowShouldClose() && !game.quitGame) {
        game.Update();
        game.Draw();
    }
    game.Unload();
    CloseWindow();
    return 0;
}