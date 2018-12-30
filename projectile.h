#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "map.h"
#include "animation.h"


class Projectile : public MovableEntity, public TengibleEntity
{

public:

    Projectile(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, sf::Vector2f speed);
    virtual bool update() = 0;
    virtual bool move(int x, int y) = 0;
    virtual ~Projectile() = 0;
};

class Torpedo : public Projectile
{

public:

    Torpedo(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention, sf::Vector2f speed);
    bool update();
    bool move(int x, int y);
    ~Torpedo();

    Animation* animation;
};

class Explosion : public TengibleEntity
{

public:

    Explosion(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    bool update();
    ~Explosion();

    Animation* animation;
};
