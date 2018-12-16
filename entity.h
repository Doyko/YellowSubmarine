#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "map.h"
#include "hitbox.h"

class Entity
{
public:

    Entity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention);
    virtual ~Entity();

    virtual void update() = 0;

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

class TengibleEntity : virtual public Entity
{
public:

    TengibleEntity(int x, int y, Map* m, sf::Texture *t, sf::IntRect dimention, Hitbox* hb);
    //virtual bool checkCollision(TengibleEntity* te);
    virtual bool checkCollision(Map* m);

    Hitbox* hitbox;
};
