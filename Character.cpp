#include "Character.h"
#include "raymath.h"


void Character::setScreenPosition(int windowWidth, int windowHeight)
{
    screenPosition = {
        windowWidth / 2.0f - (.5f * width ),
        windowHeight / 2.0f - (.5f * height)};
}

void Character::tick(float deltaTime)
{
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
        texture = run;
        direction = Vector2Normalize(direction);
        direction = Vector2Scale(direction, speed);
        worldPosition = Vector2Add(worldPosition, direction);
        rightLeft = direction.x < 0 ? -1.f : 1.f;
    }
    else
    {
        texture = idle;
    }
    // Animation Code
    // update Animation Frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle source{frame * width, 0, rightLeft * width, height};
    Rectangle destination{screenPosition.x, screenPosition.y, width * 4.0f, height * 4.0f};
    Vector2 origin{0, 0};
    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        .0f,
        WHITE);
}

Character::Character()
{
    width = idle.width/maxFrames;
    height = idle.height;
}