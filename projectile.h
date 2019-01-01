#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "animation.h"


class Projectile : public MovableEntity, public TengibleEntity
{

public:

    Projectile(int x, int y, Map* m, sf::IntRect dimention, sf::Vector2f speed);
    bool update();
    bool move(int x, int y);
    virtual ~Projectile() = 0;

    static std::vector<Projectile*> projectiles;
};

class Torpedo : public Projectile
{

public:

    Torpedo(int x, int y, Map* m, sf::IntRect dimention, sf::Vector2f speed);
    bool update();
    ~Torpedo();

    Animation* animation;
};

class Ink : public Projectile
{

public :

    Ink(int x, int y, Map* m, sf::Vector2f speed);
    ~Ink();
};

class Explosion : public TengibleEntity
{

public:

    Explosion(int x, int y, Map* m);
    bool update();
    ~Explosion();

    Animation* animation;
};
