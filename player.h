#pragma once
#include "param.h"

class Animation;

class Player : public MovableEntity, public InteractiveEntity
{

public:

    Player(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    ~Player();

    void update();
    bool interact(InteractiveEntity* te);
    bool move(int x, int y);

    Animation* anim;
    int life;
};
