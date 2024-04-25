
#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(
    Vector2 position,
    Texture2D idle_texture,
    Texture2D run_texture)
{
    worldPosition = position;
    idle = idle_texture;
    run = run_texture;
    width = idle.width / maxFrames;
    height = idle.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;
    velocity = Vector2Subtract(
        target->getScreenPosition(),
        getScreenPosition());

    if (Vector2Length(velocity) > radius) velocity = {0};

    BaseCharacter::tick(deltaTime);

    if (CheckCollisionRecs(getCollisionRec(), target->getCollisionRec()))
        target->takeDamage(damagePerSec * deltaTime);
}

Vector2 Enemy::getScreenPosition()
{
    return Vector2Subtract(
        worldPosition,
        target->getWorldPosition()
    );
}