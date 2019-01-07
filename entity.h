#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "data.h"

#define ACCELERATION 2
#define DECCELERATION 1

class Hitbox;

class Entity
{

public:

    Entity(const int x, const int y, const sf::IntRect dimension);
    virtual ~Entity();
    virtual bool update();

    int posX;
    int posY;
    sf::Sprite* sprite;
};

class MovableEntity : virtual public Entity
{

public:

    MovableEntity(const int x, const int y, const sf::IntRect dimension);
    ~MovableEntity();

    void changeSpeed(const float x, const float y);
    virtual bool move(const int x, const int y) = 0;
    
    int maxSpeed;

protected:

    int speedX;
    int speedY;
};

class TangibleEntity : virtual public Entity
{

public:

    TangibleEntity(const int x, const int y, const sf::IntRect dimension);
    ~TangibleEntity();

    virtual bool checkCollision(const TangibleEntity* te) const;
    virtual bool checkCollision() const;

    Hitbox* hitbox;
};
