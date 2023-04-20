#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

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

    // Create instances of props
    Texture2D rockTex = LoadTexture("Tileset/nature_tileset/Rock.png");
    Prop rock{Vector2{0.f, 0.f}, rockTex};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Move map texture opposite of character movement
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, mapScale, WHITE);

        // Draw the props
        rock.Render(knight.getWorldPos());
        
        knight.tick(GetFrameTime());

        // Check the map bounds
        if( knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }

        EndDrawing();
    }

    CloseWindow();
}