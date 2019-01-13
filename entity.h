#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "data.h"

#define ACCELERATION 2
#define DECCELERATION 1
#define MAXSPEED 20

class Hitbox;

enum EntityType
{
    chest,
    lifebonus,
    speedbonus,
    qfBonus,
    shark,
    octopus,
    mine,
    barricade,
};

inline std::istream& operator>>(std::istream& is, EntityType& obj)
{
    std::string s;
    is >> s;
    if(s.compare("chest") == 0)
        obj = EntityType::chest;
    else if(s.compare("lifebonus") == 0)
        obj = EntityType::lifebonus;
    else if(s.compare("speedbonus") == 0)
        obj = EntityType::speedbonus;
    else if(s.compare("qfBonus") == 0)
        obj = EntityType::qfBonus;
    else if(s.compare("shark") == 0)
        obj = EntityType::shark;
    else if(s.compare("octopus") == 0)
        obj = EntityType::octopus;
    else if(s.compare("mine") == 0)
        obj = EntityType::mine;
    else if(s.compare("barricade") == 0)
        obj = EntityType::barricade;
    return is;
}

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

    int getSpeedX() const;
    int getSpeedY() const;
    void setSpeed(int x, int y);
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
