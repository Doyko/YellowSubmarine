#pragma once
#include <SFML/Graphics.hpp>
#include "data.h"
#include "projectile.h"

class Explosion : public TangibleEntity
{

public:

    Explosion(const int x, const int y);
    ~Explosion();

    bool update();
    void trigger();

    Animation* animation;

private:

    bool triggered;

    static sf::IntRect dimension;
    static int nbSprite;
    static int animSpeed;
};

class Barricade : public TangibleEntity
{

public:

    Barricade(const int x, const int y);
    ~Barricade();

    void destroy();

private:

    static sf::IntRect dimension;
};

class Debris : public MovableEntity
{

public:

    Debris(const int x, const int y);
    ~Debris();

    bool update();

private:

    int tick;

    static sf::IntRect dimension;
};

class Bubble : public MovableEntity
{

public:

    Bubble(const int x, const int y);
    ~Bubble();

    bool update();

private:

    int tick;
    sf::Sprite* spriteBoop;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteBoop;
};

class Corpse : public MovableEntity, public TangibleEntity
{

public:

    Corpse(const int x, const int y, sf::IntRect dimension);
    ~Corpse();

    bool update();

    static sf::IntRect shark;

private:

    bool move(const int x, const int y);

    int tick;
    bool snare;
};

class Chest : public TangibleEntity
{

public:

    Chest(const int x, const int y);
    ~Chest();

    bool update();

private:

    bool open;
    sf::Sprite* spriteOpen;

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteOpen;
};
