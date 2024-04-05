#include "raylib.h"

class Character
{
private:
    Texture2D texture{}; 
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    float width{};
    float height{};
    Vector2 screenPosition{};
    Vector2 worldPosition{};



    // animation variables
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};

public:
    Vector2 getWorldPosition() { return worldPosition; }
    void setScreenPosition(int windowWidth, int windowHeight);
    void tick(float deltaTime);
    Character();
};

