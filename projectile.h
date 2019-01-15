#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "animation.h"
#include "mob.h"
#include "effect.h"

class Projectile : public MovableEntity, public TangibleEntity
{

public:

    Projectile(const int x, const int y, const sf::IntRect dimension, const sf::Vector2f speed);
    bool update();
    bool move(const int x, const int y);
    virtual ~Projectile() = 0;
};

class Torpedo : public Projectile
{

public:

    Torpedo(const int x, const int y, const sf::IntRect dimension, const sf::Vector2f speed);
    bool update();
    ~Torpedo();

    Animation* animation;
    int tick;

    static sf::IntRect dimRight;
    static sf::IntRect dimLeft;
    static sf::Vector2f speedRight;
    static sf::Vector2f speedLeft;
    static int nbSprite;
    static int animSpeed;
};

class Ink : public Projectile
{

public :

    Ink(const int x, const int y);
    ~Ink();
    bool update();


    static sf::IntRect dimension;
    static sf::Vector2f speed;
};
