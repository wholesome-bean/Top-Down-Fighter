#include "raylib.h"
#include "raymath.h"
#include "Character.h"


int main()
{
    float windowWidth{384};
    float windowHeight{384};\
    InitWindow(windowWidth, windowHeight, "Richard's Top-Down Fighter");
    SetTargetFPS(60);

    // Map Texture
    Texture2D map = LoadTexture("Tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    // Create instance of character
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Move map texture opposite of character movement
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }

    CloseWindow();
}