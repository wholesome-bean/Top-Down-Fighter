#include "Prop.h"
#include "raymath.h"

// Member initializer list avoids the initial initialization to 0 and then initializing it again to pos or tex
Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex)
{

}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}