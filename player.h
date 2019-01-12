#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hitbox.h"
#include "map.h"
#include "entity.h"
#include "animation.h"
#include "projectile.h"
#include "buff.h"

#define MAXLIFE 3
#define COOLDOWN 100

class Player : public MovableEntity, public TangibleEntity
{

public:

    Player(const int x, const int y);
    ~Player();

    bool update();
    bool move(const int x, const int y);
    void shoot();
    void setDirection(const int dir);
    int getLife() const;
    void addLife(const int amout);
    void addBuff(BuffType b, unsigned int t);

private:

    void setRotation();

    enum class AnimationIndex
    {
        moveRight,
        moveLeft,
        count,
    };
    Animation* animations[int(AnimationIndex::count)];
    AnimationIndex currentAnimation = AnimationIndex::moveRight;

    int life;
    int shootCD;
    Buff<Player> buffs;

    static sf::IntRect dimension;
    static sf::IntRect animRight;
    static sf::IntRect animLeft;
    static int nbSprite;
    static int animSpeed;
};
