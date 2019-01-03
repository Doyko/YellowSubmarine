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

    Entity(int x, int y, sf::IntRect dimension);
    virtual ~Entity();
    virtual bool update();

    int posX;
    int posY;
    sf::Sprite* sprite;
};

class MovableEntity : virtual public Entity
{

public:

    MovableEntity(int x, int y, sf::IntRect dimension);

    void changeSpeed(float x, float y);
    virtual bool move(int x, int y) = 0;

    int speedX;
    int speedY;
    int maxSpeed;
};

class TangibleEntity : virtual public Entity
{

public:

    TangibleEntity(int x, int y, sf::IntRect dimension);

    virtual bool checkCollision(TangibleEntity* te);
    virtual bool checkCollision();

    Hitbox* hitbox;
};
