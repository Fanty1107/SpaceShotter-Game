#include "game.hpp"
#include "raygui.h"

Game::Game() {
    gameLoop = false;
}

void Game::Initialize() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    bg.Load();
    ship.Load();
    plasmaSprite = LoadTexture("assets/FX/plasma_1.png");
}

void Game::Update() {
    if (gameLoop) {
        float deltaTime = GetFrameTime();
        
        // Atualiza a Nave (ela cuida do próprio movimento e tiro)
        ship.Update(deltaTime, plasmas, plasmaSprite);

        // Atualiza os Tiros
        for (int i = plasmas.size() - 1; i >= 0; i--) {
            plasmas[i].Update(deltaTime);
            
            // Apaga se sair da tela
            if (plasmas[i].posV.y < -plasmaSprite.height) {
                plasmas.erase(plasmas.begin() + i);
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE); 

    if (!gameLoop) {
        // Desenho do Menu
        ClearBackground(BLACK);
        float btnW = 200, btnH = 30;
        Rectangle buttonRec = { (SCREEN_WIDTH/2) - (btnW/2), (SCREEN_HEIGHT/2) - (btnH/2), btnW, btnH };

        DrawText("Space Shooter", SCREEN_WIDTH/2 - MeasureText("Space Shooter", FONT_SIZE)/2, (int)SCREEN_HEIGHT/4, FONT_SIZE, PURPLE);
        DrawText("Press the button to start the game", SCREEN_WIDTH/2 - MeasureText("Press the button to start the game", FONT_SIZE)/2, (int)SCREEN_HEIGHT/3, FONT_SIZE, GRAY);

        if (GuiButton(buttonRec, "Start Game")) {
            gameLoop = true;
        }
    } else {
        // Desenho do Jogo
        bg.Draw();
        
        for (auto& plasma : plasmas) {
            plasma.Draw(plasmaSprite);
            // DrawRectangleLinesEx(plasma.collider, 1, RED); // Debug
        }
        
        ship.Draw();
    }
    EndDrawing();
}

void Game::Unload() {
    bg.Unload();
    ship.Unload();
    UnloadTexture(plasmaSprite);
}