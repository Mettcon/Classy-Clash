#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>


int main()
{
    const int windowWidth{ 384 };
    const int windowHeight{ 384 };
    InitWindow(windowWidth, windowHeight, "Top Down");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{ 0.0f, 0.0f };
    const float mapScale = 4.0f;


    Character player(windowWidth, windowHeight);

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")} };

    Enemy goblin{
        Vector2{},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png") };
    goblin.setTarget(&player);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(player.getWorldPosition(), -1);
        DrawTextureEx(map, mapPosition, 0.0f, mapScale, WHITE);

        if (!player.getAlive())
        {
            DrawText("Game Over", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        std::string health = "Health: ";
        health.append(std::to_string(player.getHealth()), 0, 5);
        DrawText(health.c_str(), 55.f, 45.f, 40, RED);

        player.tick(GetFrameTime());

        Vector2 position = player.getWorldPosition();

        // TODO: Look into Clamp
        if (position.x < .0f ||
            position.y < .0f ||
            position.x + windowWidth > map.width * mapScale ||
            position.y + windowHeight > map.height * mapScale)
        {
            player.undoMovement();
        }

        Rectangle playerCollider = player.getCollisionRec();

        for (auto entry : props)
        {
            if (CheckCollisionRecs(playerCollider, entry.getCollisionRec(position)))
                player.undoMovement();
        }

        for (auto entry : props)
        {
            entry.Render(position);
        }

        goblin.tick(GetFrameTime());

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionRecs(goblin.getCollisionRec(), player.getWeaponCollisionRec()))
                goblin.setAlive(false);
        }

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}