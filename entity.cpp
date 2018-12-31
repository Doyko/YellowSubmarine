#include "entity.h"
#include <iostream>

std::vector<Entity*> Entity::entities;

Entity::Entity(int x, int y, Map* m, sf::IntRect dimention)
:
    posX(x),
    posY(y),
    map(m)
{
    sprite = new sf::Sprite(Texture::textureEntity, dimention);
    sprite->setPosition(posX,posY);
    //std::cout << "constructor Entity" << std::endl;
}

Entity::~Entity()
{
    delete sprite;
}

bool Entity::update()
{
    return true;
}

MovableEntity::MovableEntity(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
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

TengibleEntity::TengibleEntity(int x, int y, Map* m, sf::IntRect dimention):
    Entity(x, y, m, dimention),
    hitbox(new Hitbox(*Texture::hitboxEntity, dimention))
{
    //std::cout << "constructor TengibleEntity" << std::endl;
}

bool TengibleEntity::checkCollision(TengibleEntity* te)
{
    return hitbox->checkCollision(posX, posY, te->hitbox, te->posX, te->posY);
}

bool TengibleEntity::checkCollision(Map* m)
{
    return hitbox->checkCollision(posX, posY, m);
}
