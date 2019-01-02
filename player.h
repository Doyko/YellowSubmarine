#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hitbox.h"
#include "map.h"
#include "entity.h"
#include "animation.h"
#include "projectile.h"

#define MAXLIFE 100
#define COOLDOWN 20

class Player : public MovableEntity, public TengibleEntity
{

public:

    Player(int x, int y);
    bool update();
    bool move(int x, int y);
    void shoot();
    void setRotation();
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
    int shootCD;

    static sf::IntRect dimension;
    static sf::IntRect animRight;
    static sf::IntRect animLeft;
    static int nbSprite;
    static int animSpeed;
};
