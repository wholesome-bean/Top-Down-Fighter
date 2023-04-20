#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    Vector2 getWorldPos() { return worldPos; }
    void tick(float deltaTime);
    void undoMovement();
    Rectangle getCollisionRec();

private:
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};

    // Character Stats
    float damage{};

    // 1 : facing right -1 : facing left
    float rightLeft{1.f};

    // Animation Variables
    float runningTime{};
    float width{};
    float height{};
    float updateTime{1.f / 12.f};
    float scale = 4.0;
    int maxFrames{6};
    const float speed{4.0};
    int frame{};
};