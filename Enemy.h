#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
private:
Character* target;
float damagePerSec{10};
float radius{25.f};
public:
    Enemy(Vector2 position, Texture2D idle_Texture, Texture2D run_texture);
    virtual void tick(float deltaTime) override;
    void setTarget(Character* Target) { target = Target; }
    virtual Vector2 getScreenPosition() override;
};