#include "raylib.h"
#include "raymath.h"
#include "character.h"

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Top Down");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0f, 0.0f};

    Character player;
    player.setScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(player.getWorldPosition(), -1 );
        DrawTextureEx(map, mapPosition, 0.0f, 4.0f, WHITE);

        player.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}