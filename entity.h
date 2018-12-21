#pragma once
#include "param.h"

#define ACCELERATION 2
#define DECCELERATION 1

class Map;
class Hitbox;

class Entity
{

public:

    Entity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention);
    virtual ~Entity();

    int posX;
    int posY;
    sf::Sprite* sprite;
    Map* map;
};

class MovableEntity : virtual public Entity
{

public:

    MovableEntity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention);

    void changeSpeed(float x, float y);
    virtual bool move(int x, int y) = 0;

    int speedX;
    int speedY;
    int maxSpeed;
};

class InteractiveEntity : virtual public Entity
{

public:

    //InteractiveEntity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention, Hitbox* hb);
    InteractiveEntity(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);

    virtual bool checkCollision(InteractiveEntity* te);
    virtual bool checkCollision(Map* m);
    virtual bool interact(InteractiveEntity* ie) = 0;

    Hitbox* hitbox;
};
