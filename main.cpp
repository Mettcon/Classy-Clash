#include "raylib.h"
#include "raymath.h"

int main()
{
    const int width = 384;
    const int height = 384;
    InitWindow(width, height, "Top Down");

    const float speed = 4;
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0f, 0.0f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0f;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0f;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0f;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0f;

        if (Vector2Length(direction) != 0.0f)
        {
            direction = Vector2Normalize(direction);
            direction = Vector2Scale(direction, speed);
            mapPosition = Vector2Subtract(mapPosition, direction);
        }
        DrawTextureEx(map, mapPosition, 0.0f, 4.0f, WHITE);

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}