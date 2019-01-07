#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "data.h"
#include "projectile.h"

class Explosion : public TangibleEntity
{

public:

    Explosion(const int x, const int y);
    bool update();
    void trigger();
    ~Explosion();

    Animation* animation;

private:

    bool triggered;

    static sf::IntRect dimension;
    static int nbSprite;
    static int animSpeed;
};


class Debris : public MovableEntity
{

public:

    Debris(const int x, const int y);
    bool update();
    bool move(const int x, const int y);
    ~Debris();

private:

    int tick;

    static sf::IntRect dimension;
};

class Bubble : public MovableEntity
{

public:

    Bubble(const int x, const int y);
    bool update();
    bool move(const int x, const int y);
    ~Bubble();

private:

    int tick;
    sf::Sprite* spriteBoop;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteBoop;
};

class Barricade : public TangibleEntity
{

public:

    Barricade(const int x, const int y);
    ~Barricade();

private:

    static sf::IntRect dimension;
};

class Chest : public TangibleEntity
{

public:

    Chest(const int x, const int y);
    bool update();
    ~Chest();

private:

    bool open;
    sf::Sprite* spriteOpen;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteOpen;
};
