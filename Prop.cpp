#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 worldPosition, Texture2D texture) :
    texture(texture),
    worldPosition(worldPosition)
{

}

void Prop::Render(Vector2 playerPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, playerPosition) };
    DrawTextureEx(texture, screenPosition, .0f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 playerPosition)
{
    Vector2 screenPosition{ Vector2Subtract(worldPosition, playerPosition) };
    return Rectangle{
        screenPosition.x,
        screenPosition.y,
        texture.width * scale,
        texture.height * scale
    };
}