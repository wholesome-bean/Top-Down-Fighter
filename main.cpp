#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    float windowWidth{384};
    float windowHeight{384};
    const float mapScale{4.0};
    InitWindow(windowWidth, windowHeight, "Richard's Top-Down Fighter");
    SetTargetFPS(60);

    // Map Texture
    Texture2D map = LoadTexture("Tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    // Create instance of character
    Character knight(windowWidth, windowHeight);

    // Create instances of enemies
    Enemy goblin(Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
    Enemy slime(Vector2{500.f, 700.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png"));\

    Enemy* enemies[]{
        &goblin,
        &slime
    };

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }
    

    // Create instances of props
    Texture2D rockTex = LoadTexture("Tileset/nature_tileset/Rock.png");
    Texture2D logTex = LoadTexture("Tileset/nature_tileset/Log.png");

    Prop props[2]
    {
        Prop{Vector2{600.f, 300.f}, rockTex},
        Prop{Vector2{400.f, 500.f}, logTex}
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Move map texture opposite of character movement
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        for(auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if(!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }
        
        knight.tick(GetFrameTime());

        // Check the map bounds
        if( knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check collision with props
        for(auto prop: props)
        {
            if(CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            }
        }

        for(auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for(auto enemy : enemies)
            {
                if(CheckCollisionRecs(knight.getWeaponCollisionRec(), enemy->getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
            
        }

        EndDrawing();
    }

    CloseWindow();
}