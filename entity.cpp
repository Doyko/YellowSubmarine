#include "entity.h"
#include <iostream>

Entity::Entity(int x, int y, sf::IntRect dimension)
:
    posX(x),
    posY(y)
{
    sprite = new sf::Sprite(Data::textureEntity, dimension);
    sprite->setPosition(posX, posY);
    //std::cout << "constructor Entity" << std::endl;
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

MovableEntity::MovableEntity(int x, int y, sf::IntRect dimension)
:
    Entity(x, y, dimension),
    speedX(0),
    speedY(0),
    maxSpeed(20)
{
    //std::cout << "constructor MovableEntity" << std::endl;
}

void MovableEntity::changeSpeed(float x, float y)
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

TangibleEntity::TangibleEntity(int x, int y, sf::IntRect dimension):
    Entity(x, y, dimension),
    hitbox(new Hitbox(*Data::hitboxEntity, dimension))
{
    //std::cout << "constructor TangibleEntity" << std::endl;
}

bool TangibleEntity::checkCollision(TangibleEntity* te)
{
    return hitbox->checkCollision(posX, posY, te->hitbox, te->posX, te->posY);
}

bool TangibleEntity::checkCollision()
{
    return hitbox->checkCollision(posX, posY);
}
