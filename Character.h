#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int width, int height);
    void tick(float deltaTime);

private:
    
};

