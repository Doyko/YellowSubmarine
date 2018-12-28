#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hitbox.h"
#include "map.h"
#include "entity.h"
#include "param.h"
#include "animation.h"

#define MAXLIFE 3

class Player : public MovableEntity, public TengibleEntity
{

public:

    Player(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    void update();
    bool move(int x, int y);
    ~Player();

    enum class AnimationIndex
    {
        moveRight,
        moveLeft,
        count,
    };
    Animation animations[int(AnimationIndex::count)];
    AnimationIndex currentAnimation = AnimationIndex::moveRight;

    int life;
};
