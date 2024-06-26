
#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
class BaseCharacter
{
private:
    bool alive{true};

protected:
    Texture2D texture{}; // = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");

    Vector2 worldPosition{};
    Vector2 worldPositionLastFrame{};

    // animation variables
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

public:
    BaseCharacter();
    Vector2 getWorldPosition() { return worldPosition; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPosition() = 0;
    bool getAlive() { return alive; };
    void setAlive(bool Alive) { alive = Alive; };
};
#endif