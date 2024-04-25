#include "Character.h"
#include "raymath.h"

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0f;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = { .0f, weapon.height * scale };
        offset = { 35.f, 55.f };
        weaponCollider = {
            getScreenPosition().x + offset.x,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : .0f;
    }
    else
    {
        origin = { weapon.width * scale, weapon.height * scale };
        offset = { 25.f, 55.f };
        weaponCollider = {
            getScreenPosition().x + offset.x - weapon.width * scale,
            getScreenPosition().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale };
        rotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : .0f;
    }

    // draw the sword
    Rectangle source{
        .0f,
        .0f,
        weapon.width * rightLeft,
        static_cast<float>(weapon.height) };

    Rectangle destination{
        getScreenPosition().x + offset.x,
        getScreenPosition().y + offset.y,
        weapon.width * scale,
        weapon.height * scale };

    DrawTexturePro(
        weapon,
        source,
        destination,
        origin,
        rotation,
        WHITE);

    DrawRectangleLines(
        weaponCollider.x,
        weaponCollider.y,
        weaponCollider.width,
        weaponCollider.height,
        RED);
}

Character::Character(int WindowWidth, int WindowHeight) :
    windowWidth(WindowWidth),
    windowHeight(WindowHeight)
{
    width = idle.width / maxFrames;
    height = idle.height;
}

Vector2 Character::getScreenPosition()
{
    return Vector2{
        windowWidth / 2.0f - scale * (.5f * width),
        windowHeight / 2.0f - scale * (.5f * height) };
}

void Character::takeDamage(float Damage)
{
    health -= Damage;
    if (health <= 0.f)
        setAlive(false);
};