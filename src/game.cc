#include "game.hpp"
#include "gameObjects.hpp"
#include "raygui.h"
#include <raylib.h>
#include <vector>

Game::Game() {
    gameLoop = false;
    spawnTimer = 0.0f;
    pontos = 0;
}

void Game::Initialize() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    bg.Load();
    ship.Load();
    plasmaSprite = LoadTexture("assets/FX/plasma_1.png");
    plasmaSpriteEnemy = LoadTexture("assets/FX/vulcan_1.png");

    enemySprite = LoadTexture("assets/Enemies/enemy_1_b_m.png");
    enemySpriteWhite = LoadTexture("assets/Enemies/enemy_1_b_m_white.png");
}

void Game::Update() {
    if (gameLoop) {
        float deltaTime = GetFrameTime();
        
        ship.Update(deltaTime, plasmas, plasmaSprite);
        //sem spawn caso player morra e spawn caso não morra
        if (!ship.isDead) {
            spawnTimer += deltaTime;
            if (spawnTimer >= 2.0f) { 
                float randomX = GetRandomValue(50, SCREEN_WIDTH - 50); 
                enemies.push_back(Enemy(randomX));
                spawnTimer = 0.0f;
            }
        }

        // --- ATUALIZA INIMIGOS ---
        for (int i = enemies.size() - 1; i >= 0; i--) {
            enemies[i].Update(deltaTime, enemyPlasmas, plasmaSpriteEnemy, enemySprite);
            
            //apaga o inimigo se ele sair pelo fundo da tela
            if (enemies[i].posV.y > SCREEN_HEIGHT) {
                enemies.erase(enemies.begin() + i);
            }
        }

        //atualiza tiros(player)
        for (int i = plasmas.size() - 1; i >= 0; i--) {
            plasmas[i].Update(deltaTime);
            
            // Apaga se sair da tela
            if (plasmas[i].posV.y < -plasmaSprite.height) {
                plasmas.erase(plasmas.begin() + i);
            }
        }
        //atualuiza tiros(enemy)
        for (int i = enemyPlasmas.size() - 1; i >= 0; i--) {
            enemyPlasmas[i].Update(deltaTime);
            if (enemyPlasmas[i].posV.y > SCREEN_HEIGHT) {
                enemyPlasmas.erase(enemyPlasmas.begin() + i);
            }
        }

        //sistema de dano
        // Checa se o tiro do player (plasmas) atingiu os inimigos
        for (int i = enemies.size() - 1; i >= 0; i--) {
            for (int j = plasmas.size() - 1; j >= 0; j--) {
                if (CheckCollisionRecs(enemies[i].collider, plasmas[j].collider)) {
                   
                    plasmas.erase(plasmas.begin() + j); // Destrói o tiro
                    if (enemies[i].blinkTimer <= 0.0f) {
                        enemies[i].hp--;
                        enemies[i].blinkTimer = 0.5f; // Pisca de branco por meio segundo
                    }
                    break; // Sai do laço de tiros, pois já acertou
                }
            }
            
            if (!ship.isDead && ship.blinkTimer <= 0.0f) {
            
            // Dano dos tiros inimigos
            for (int j = enemyPlasmas.size() - 1; j >= 0; j--) {
                if (CheckCollisionRecs(ship.collider, enemyPlasmas[j].collider)) {
                    ship.hp--;
                    ship.blinkTimer = 0.5f;
                    enemyPlasmas.erase(enemyPlasmas.begin() + j);
                    break;
                }
            }

            // Dano corpo a corpo encostando no inimigo
            if (ship.blinkTimer <= 0.0f) { // Checa de novo para não tomar dano duplo no mesmo frame
                for (size_t i = 0; i < enemies.size(); i++) {
                    if (CheckCollisionRecs(ship.collider, enemies[i].collider)) {
                        ship.hp--;
                        ship.blinkTimer = 0.5f;
                        // Inimigo também toma um dano ao esbarrar na nave
                        if (enemies[i].blinkTimer <= 0.0f) {
                            enemies[i].hp--;
                            enemies[i].blinkTimer = 0.5f;
                        }
                        break; 
                    }
                }
            }
        }

        // --- CHECA AS MORTES ---
        // Limpa os inimigos sem vida
        for (int i = enemies.size() - 1; i >= 0; i--) {
            if (enemies[i].hp <= 0) {
                pontos += 10;
                enemies.erase(enemies.begin() + i);
            }
        }
        
        // Ativa o Game Over
        if (ship.hp <= 0 && !ship.isDead) {
            ship.isDead = true;
            // Nesse ponto a tela de Game Over vai aparecer
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
        //enemy spawn/shot/animations
        for (auto& ePlasma : enemyPlasmas) ePlasma.Draw(plasmaSpriteEnemy);
        for (auto& e : enemies) e.Draw( enemySprite, enemySpriteWhite);
        
        ship.Draw();
    }
    DrawText(TextFormat("HP: %d", ship.hp), 10, 10, 20, GREEN);
    DrawText(TextFormat("Points: %d", pontos), 700, 10, 20, RED);
    if (ship.isDead) {
            DrawText("GAME OVER", SCREEN_WIDTH/2 - MeasureText("GAME OVER", 50)/2, SCREEN_HEIGHT/2, 50, RED);
        }
    EndDrawing();
}

void Game::Unload() {
    bg.Unload();
    ship.Unload();
    UnloadTexture(enemySpriteWhite);
    UnloadTexture(plasmaSprite);
    UnloadTexture(plasmaSpriteEnemy);
    UnloadTexture(enemySprite);
}