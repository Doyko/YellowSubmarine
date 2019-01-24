#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "animation.h"
#include "projectile.h"
#include "buff.h"

#define COOLDOWN 100
#define MAXSPEED 20

class Player : public MovableEntity, public TangibleEntity
{

public:

    Player(const int x, const int y);
    ~Player();

    bool update();
    void shoot();
    void setDirection(const int dir);
    void setPosition(const int x, const int y);
    int getLife() const;
    int getDistance(const int x, const int y) const;
    void addLife(const int amount);
    void setMaxLife();
    void setMaxSpeed();
    int getCD() const;
    void addCD(const int i);
    void addBuff(const buffType b, const unsigned int t);
    void clearBuff();

private:

    void setRotation();
    void setColorSprite();
    void setSound();

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
    static std::pair<int,int> center;
    static sf::IntRect animRight;
    static sf::IntRect animLeft;
    static int nbSprite;
    static int animSpeed;
};
