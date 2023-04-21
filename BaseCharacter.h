#ifndef BASE_CHARACTER_H // If not already defined - avoids adding the code twice
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    bool getAlive() { return alive; };
    void setAlive(bool isAlive) { alive = isAlive; };

    // pure virtual function
    // makes BaseCharacter an abstract class as well
    // so you cannot create an instance of this base class; only derive
    virtual Vector2 getScreenPos() = 0;

protected:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    //Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // 1 : facing right -1 : facing left
    float rightLeft{1.f};

    // Animation Variables
    float runningTime{};
    float width{};
    float height{};
    float updateTime{1.f / 12.f};
    float scale = 4.0;
    int maxFrames{6};
    float speed{4.0};
    int frame{};
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif