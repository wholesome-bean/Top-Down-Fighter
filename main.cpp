#include "raylib.h"
#include "raymath.h"

int main()
{
    // Window Details
    double windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Fantasy Clash");
    SetTargetFPS(60);

    // Map Texture
    Texture2D map = LoadTexture("Tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    // Movement
    float speed{4.0};

    // Knight Texture
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowDimensions[0]/2.0f - 4.0f * (0.5 * (float)knight.width)/6.0,
        (float)windowDimensions[1]/2.0f - 4.0f * (0.5 * (float)knight.height)
    };
    // 1 : facing right -1 : facing left
    float rightLeft{1.f};

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

    // Animation Variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Movement
        Vector2 direction{};
        if(IsKeyDown(KEY_A)) direction.x -= 1.0;
        if(IsKeyDown(KEY_D)) direction.x += 1.0;
        if(IsKeyDown(KEY_W)) direction.y -= 1.0;
        if(IsKeyDown(KEY_S)) direction.y += 1.0;
        
        if(Vector2Length(direction) != 0)
        {
            // Normalize to avoid moving faster diagonally
            mapPos = (Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed)));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        } else knight = knight_idle;
        
        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if(frame > maxFrames) frame = 0;
        }

        // Draw the knight
        // source selects which animation frame to use from sprite sheet
        Rectangle source{frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.f, 4.f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);


        EndDrawing();
    }

    CloseWindow();
}