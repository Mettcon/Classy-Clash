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

    Texture2D enemyIdle = LoadTexture("characters/goblin_idle_spritesheet.png");
    Texture2D enemyRun = LoadTexture("characters/goblin_run_spritesheet.png");
    Character player(windowWidth, windowHeight);

    Prop props[2]{
        Prop{Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.0f, 500.0f}, LoadTexture("nature_tileset/Log.png")} };



    Enemy enemies[]{
        Enemy{Vector2{}, enemyIdle, enemyRun},
        Enemy{Vector2{windowWidth, windowHeight}, enemyIdle, enemyRun},
        Enemy{Vector2{175, 175}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")},
    };
/*
    Enemy goblin{
        Vector2{},
        enemyIdle,
        enemyRun
    };
*/
    //goblin.setTarget(&player);
    for (auto entry : enemies) entry.setTarget(&player);

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

        //goblin.tick(GetFrameTime());
        for (auto entry : enemies) entry.tick(GetFrameTime());

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            //if (CheckCollisionRecs(goblin.getCollisionRec(), player.getWeaponCollisionRec()))
            //    goblin.setAlive(false);

            for (auto entry : enemies)
            {
                if (CheckCollisionRecs(entry.getCollisionRec(), player.getWeaponCollisionRec()))
                    entry.setAlive(false);
            }
        }

        EndDrawing();
    }
    CloseWindow();
    UnloadTexture(map);
}