#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "data.h"
#include "projectile.h"

class Explosion : public TangibleEntity
{

public:

    Explosion(int x, int y);
    bool update();
    void trigger();
    ~Explosion();

    Animation* animation;
    bool triggered;

    static sf::IntRect dimension;
    static sf::Vector2f speed;
    static int nbSprite;
    static int animSpeed;
};


class Debris : public MovableEntity
{

public:

    Debris(int x, int y);
    bool update();
    bool move(int x, int y);
    ~Debris();

    int tick;

    static sf::IntRect dimension;
};

class Bubble : public MovableEntity
{

public:

    Bubble(int x, int y);
    bool update();
    bool move(int x, int y);
    ~Bubble();

    int tick;
    sf::Sprite* spriteBoop;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteBoop;
};
