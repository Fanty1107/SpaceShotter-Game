#include "game.hpp"
#include "animation.hpp"
#include "gameObjects.hpp"
#include "raygui.h"
#include <raylib.h>
#include <vector>

Game::Game() {
    gameLoop = false;
    gameEVA = false;
    gameNormal = false;
    spawnTimer = 0.0f;
    spawnRate = 2.0f;
    pontos = 0;
    quitGame = false;
}

void Game::Initialize() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
    bg.Load();
    ship.Load();
    plasmaSprite = LoadTexture("assets/FX/plasma_1.png");
    plasmaSpriteEnemy = LoadTexture("assets/FX/vulcan_1.png");

    enemySprite = LoadTexture("assets/Enemies/enemy_1_b_m.png");
    enemySpriteWhite = LoadTexture("assets/Enemies/enemy_1_b_m_white.png");

    std::vector<Texture2D> expFrames = {
        LoadTexture("assets/Explosions/explosion_1_01.png"),
        LoadTexture("assets/Explosions/explosion_1_02.png"),
        LoadTexture("assets/Explosions/explosion_1_03.png"),
        LoadTexture("assets/Explosions/explosion_1_04.png"),
        LoadTexture("assets/Explosions/explosion_1_05.png"),
        LoadTexture("assets/Explosions/explosion_1_06.png"),
        LoadTexture("assets/Explosions/explosion_1_07.png"),
        LoadTexture("assets/Explosions/explosion_1_08.png"),
        LoadTexture("assets/Explosions/explosion_1_09.png"),
        LoadTexture("assets/Explosions/explosion_1_10.png"),
        LoadTexture("assets/Explosions/explosion_1_11.png")
    };
    explosionAnimGlobal = MultiImageAnimation(expFrames, 0.1f);

    InitAudioDevice();
    eva = LoadSound("assets/sound/eva.mp3");
    explosion = LoadSound("assets/sound/boom.mp3");
    coolSong = LoadSound("assets/sound/coolSong.mp3");
    gameOver = LoadSound("assets/sound/gameOver.mp3");
    SetSoundVolume(coolSong, 0.3f);
    SetSoundVolume(explosion, 0.2f);
}

void Game::Update() {
    if (gameLoop) {
        float deltaTime = GetFrameTime();
        
        ship.Update(deltaTime, plasmas, plasmaSprite);
        //sem spawn caso player morra e spawn caso não morra
        if (!ship.isDead) {
            spawnTimer += deltaTime;
            if (spawnTimer >= spawnRate) { 
                float randomX = GetRandomValue(50, SCREEN_WIDTH - 50); 
                enemies.push_back(Enemy(randomX));
                spawnTimer = 0.0f;
            }
            if(spawnRate > 0.6f && gameNormal == true){
                spawnRate -= 0.01f;
            }
            else if(spawnRate > 0.4f && gameEVA == true){
                spawnRate -= 0.08f;
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
                    break; 
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

        //atualiza explosões
        for (int i = explosions.size() - 1; i >= 0; i--) {
            explosions[i].Update(deltaTime);
            // Se o tempo de vida acabou, apaga a explosão
            if (explosions[i].lifeTime <= 0.0f) {
                explosions.erase(explosions.begin() + i);
            }
        }

        // --- CHECA AS MORTES DOS INIMIGOS ---
        for (int i = enemies.size() - 1; i >= 0; i--) {
            if (enemies[i].hp <= 0) {
                // 1. Cria uma explosão exatamente na posição do inimigo
                explosions.push_back(Explosion(enemies[i].posV, explosionAnimGlobal));    
                 
                PlaySound(explosion);
                // 2. Apaga o inimigo da memória
                enemies.erase(enemies.begin() + i);
                pontos+=10;
            }
        }   
        
        // Ativa o Game Over
        if (ship.hp <= 0 && !ship.isDead) {
            ship.isDead = true;
            if(IsSoundPlaying(eva)){
                StopSound(eva);
            }
             if(IsSoundPlaying(coolSong)){
                StopSound(coolSong);
            }
            PlaySound(gameOver);
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
        Rectangle buttonEVA = {(SCREEN_WIDTH/2) - (btnW/2), (SCREEN_HEIGHT/2 - 50) - (btnH/2), btnW, btnH};
        Rectangle buttonQuit = {(SCREEN_WIDTH/2) - (btnW/2), (SCREEN_HEIGHT/2 + 50) - (btnH/2), btnW, btnH};

        DrawText("COOL Space Shooter", SCREEN_WIDTH/2 - MeasureText("COOL Space Shooter", FONT_SIZE)/2, (int)SCREEN_HEIGHT/4, FONT_SIZE, PURPLE);
        DrawText("Press the button to start the game", SCREEN_WIDTH/2 - MeasureText("Press the button to start the game", FONT_SIZE)/2, (int)SCREEN_HEIGHT/3, FONT_SIZE, GRAY);

        if (GuiButton(buttonRec, "Start Game")) {
            StopSound(gameOver);
            PlaySound(coolSong);
            gameLoop = true;
            gameNormal = true;
            spawnRate = 10.0f; 
            spawnTimer = 0.0f;
            ship.fireRate = 0.4f;
            ship.hp = 5;
            ship.isDead = false;
            enemies.clear();
            plasmas.clear();
            enemyPlasmas.clear();
            explosions.clear();
        }
        if(GuiButton(buttonEVA, "Evangelion")){
            StopSound(gameOver);
            PlaySound(eva);
            gameLoop = true;
            gameEVA = true;
            ship.fireRate = 0.1f;
            spawnRate = 2.0f;
            spawnTimer = 0.0f;
            ship.hp = 5;
            ship.isDead = false;
            enemies.clear();
            plasmas.clear();
            enemyPlasmas.clear();
            explosions.clear();
        }
        if(GuiButton(buttonQuit, "Exit")){
            quitGame = true;
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
        for(auto& exp : explosions) exp.Draw();
        
        ship.Draw();
    
    DrawText(TextFormat("HP: %d", ship.hp), 10, 10, 20, GREEN);
    DrawText(TextFormat("Points: %d", pontos), 670, 10, 20, RED);
    if (ship.isDead) {

            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.7f));

            DrawText("GAME OVER NOOB", SCREEN_WIDTH/2 - MeasureText("GAME OVER NOOB", 60)/2, SCREEN_HEIGHT/4, 60, RED);

            float btnW = 200, btnH = 40;
            Rectangle tryAgainBtn = { (SCREEN_WIDTH/2) - (btnW/2), (SCREEN_HEIGHT/2), btnW, btnH };
            Rectangle quitBtn = { (SCREEN_WIDTH/2) - (btnW/2), (SCREEN_HEIGHT/2) + btnH + 20, btnW, btnH };

            if(GuiButton(tryAgainBtn, "Try Again")){
                gameLoop = false;
            }
            if(GuiButton(quitBtn, "Quit")){
                quitGame = true;
            }
        }
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
    UnloadSound(eva);
    UnloadSound(explosion);
    UnloadSound(coolSong);
    UnloadSound(gameOver);
    for (auto& tex : explosionAnimGlobal.frames) {
        UnloadTexture(tex);
    }
    CloseAudioDevice();
}