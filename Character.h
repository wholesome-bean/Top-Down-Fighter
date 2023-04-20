#include "raylib.h"

class Character
{

public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);
    Character();

private:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};

    // Character Stats
    float damage{};
    
    // 1 : facing right -1 : facing left
    float rightLeft{1.f};

    // Animation Variables
    float runningTime{};
    float width{};
    float height{};
    float updateTime{1.f / 12.f};
    int maxFrames{6};
    const float speed{4.0};
    int frame{};
};

