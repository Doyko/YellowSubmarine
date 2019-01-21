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

    static sf::IntRect octopus;
    static sf::IntRect shark;
    static sf::IntRect jellyfish;

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

    static sf::IntRect dimension;
    static sf::IntRect dimSpriteOpen;
};

class Current : public TangibleEntity
{

public:

    Current(const int x, const int y, const int dir);
    ~Current();

    bool update();

    Animation* animation;

private:

    void moveEntity(MovableEntity* me);

    int direction; //0 = up, 1 = down, 2 = left, 3 = right

    static sf::IntRect dimension;
    static int nbSprite;
    static int animSpeed;
};
