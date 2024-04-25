#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
private:
    int windowWidth{};
    int windowHeight{};
    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollider{};
    float health{100.f};

public:
    virtual void tick(float deltaTime) override;
    Character(int windowWidth, int windowHeight);
    virtual Vector2 getScreenPosition() override;
    Rectangle getWeaponCollisionRec() const { return weaponCollider; };
    float getHealth() const { return health; }
    void takeDamage(float Damage );
};
#endif