#include "raylib.h"
#include "raymath.h"

class Character
{

public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};

    // Character Stats
    float damage{};
    const float speed{4.0};

    // 1 : facing right -1 : facing left
    float rightLeft{1.f};

    // Animation Variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
};

// :: "fully qualifying function name"
void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos =
        {
            (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width) / 6.0f,
            (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float deltaTime)
{
    // Movement
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0)
    {
        // Normalize to avoid moving faster diagonally
        // set worldPos = worldPos + direction
        worldPos = (Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed)));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = knight_run;
    }
    else
        texture = knight_idle;

    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // Draw the knight
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.f, 4.f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

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