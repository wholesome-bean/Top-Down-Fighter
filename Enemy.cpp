#include "Enemy.h" 
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;

    speed = 3.5f;
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

void Enemy::tick(float deltaTime)
{
    if(!getAlive()) return;

    // Get toTarget
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {0};

    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
}