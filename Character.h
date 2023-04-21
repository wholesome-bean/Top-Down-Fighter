#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int width, int height);
    virtual void tick(float deltaTime) override;

private:
    
};

