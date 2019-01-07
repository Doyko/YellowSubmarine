#include "entity.h"
#include <iostream>

Entity::Entity(const int x, const int y, const sf::IntRect dimension)
:
    posX(x),
    posY(y)
{
    sprite = new sf::Sprite(Data::textureEntity, dimension);
    sprite->setPosition(posX, posY);
}

Entity::~Entity()
{
    if(sprite != NULL)
    {
        delete sprite;
    }
}

bool Entity::update()
{
    return false;
}

MovableEntity::MovableEntity(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    maxSpeed(20),
    speedX(0),
    speedY(0)
{}

void MovableEntity::changeSpeed(const float x, const float y)
{
    speedX += x;
    speedY += y;

    if(speedX > maxSpeed)
        speedX = maxSpeed;
    else if(speedX < -maxSpeed)
        speedX = -maxSpeed;

    if(speedY > maxSpeed)
        speedY = maxSpeed;
    else if(speedY < -maxSpeed)
        speedY = -maxSpeed;
}

TangibleEntity::TangibleEntity(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    hitbox(new Hitbox(*Data::hitboxEntity, dimension))
{}

bool TangibleEntity::checkCollision(const TangibleEntity* te) const
{
    return hitbox->checkCollision(posX, posY, te->hitbox, te->posX, te->posY);
}

bool TangibleEntity::checkCollision() const
{
    return hitbox->checkCollision(posX, posY);
}
