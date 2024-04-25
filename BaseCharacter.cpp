#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale };
}

void BaseCharacter::undoMovement()
{
    worldPosition = worldPositionLastFrame;
}

void BaseCharacter::tick(float deltaTime)
{
    worldPositionLastFrame = worldPosition;
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

    if (Vector2Length(velocity) != 0.0f)
    {
        texture = run;
        velocity = Vector2Normalize(velocity);
        velocity = Vector2Scale(velocity, speed);
        worldPosition = Vector2Add(worldPosition, velocity);
        rightLeft = velocity.x < .0f ? -1.f : 1.f;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    Rectangle source{ frame * width, 0, rightLeft * width, height };
    Rectangle destination{
        getScreenPosition().x,
        getScreenPosition().y,
        width * scale,
        height * scale };

    Vector2 origin{ 0, 0 };
    DrawTexturePro(
        texture,
        source,
        destination,
        origin,
        .0f,
        WHITE);
}