#include "Character.h"
#include "raymath.h"

// :: "fully qualifying function name"
void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos =
        {
            (float)winWidth / 2.0f - 4.0f * (0.5f * width),
            (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}

void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

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
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}
