#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "animation.h"


class Projectile : public MovableEntity, public TengibleEntity
{

public:

    Projectile(int x, int y, sf::IntRect dimention, sf::Vector2f speed);
    bool update();
    bool move(int x, int y);
    virtual ~Projectile() = 0;

    static std::vector<Projectile*> projectiles;
};

class Torpedo : public Projectile
{

public:

    Torpedo(int x, int y, sf::IntRect dimention, sf::Vector2f speed);
    bool update();
    ~Torpedo();

    Animation* animation;

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

    Ink(int x, int y);
    ~Ink();


    static sf::IntRect dimension;
    static sf::Vector2f speed;
};

class Explosion : public TengibleEntity
{

public:

    Explosion(int x, int y);
    bool update();
    ~Explosion();

    Animation* animation;

    static sf::IntRect dimension;
    static int nbSprite;
    static int animSpeed;
};
