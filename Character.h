#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"
#include <string>

class Character : public BaseCharacter
{
public:
    Character(int width, int height);
    virtual Vector2 getScreenPos() override;
    virtual void tick(float deltaTime) override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec ; };
    float getHealth() const { return health; };
    void takeDamage(float damage);

private:
    int windowWidth;
    int windowHeight;
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRec{};
    float health{100.f};
};

#endif