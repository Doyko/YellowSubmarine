#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hitbox.h"
#include "map.h"
#include "entity.h"
#include "param.h"
#include "animation.h"

class Player : public MovableEntity, public TengibleEntity
{
    public:

    Player(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention);
    void update();
    bool move(int x, int y);
    ~Player();

    Animation* anim;
};
