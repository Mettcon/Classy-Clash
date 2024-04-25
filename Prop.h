#include "raylib.h"

class Prop
{
private:
    Texture2D texture{};
    Vector2 worldPosition{};

    float scale{4.0f};


public:
    Prop(Vector2 worldPosition, Texture2D texture);
    void Render( Vector2 playerPosition);
    Rectangle getCollisionRec( Vector2 playerPosition );
};