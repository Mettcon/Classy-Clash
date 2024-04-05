#include "raylib.h"
#include "raymath.h"

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Top Down");

    const float speed = 4;
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0f, 0.0f};

    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight ;
    Vector2 knightPosition{
        // half window width to find the center and move additional half of 1 element of the sprite sheet.
        windowWidth / 2.0f - (.5f * knight_idle.width / 6.0f),
        windowHeight / 2.0f - (.5f * knight_idle.height)};

    // animation variables
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};

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
            knight = knight_run;
            direction = Vector2Normalize(direction);
            direction = Vector2Scale(direction, speed);
            mapPosition = Vector2Subtract(mapPosition, direction);
            rightLeft = direction.x < 0 ? -1.f : 1.f;
        } else {
            knight = knight_idle;
        }
        DrawTextureEx(map, mapPosition, 0.0f, 4.0f, WHITE);

        // update Animation Frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0;
        }

        Rectangle source{frame * knight.width/6, 0, rightLeft * (float)knight.width / 6, (float)knight.height};
        Rectangle destination{knightPosition.x, knightPosition.y, knight.width / 6 * 4.0f, knight.height * 4.0f};
        Vector2 origin{0, 0};
        DrawTexturePro(
            knight,
            source,
            destination,
            origin,
            .0f,
            WHITE);

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}