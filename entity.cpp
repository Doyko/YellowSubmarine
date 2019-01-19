#include "entity.h"

//-----Entity-----

Entity::Entity(const int x, const int y, const sf::IntRect dimension)
:
    posX(x),
    posY(y),
    sprite(new sf::Sprite(Data::textureEntity, dimension))
{
    sprite->setPosition(posX, posY);
}

Entity::~Entity()
{
    if(sprite != NULL)
    {
        delete sprite;
        sprite = NULL;
    }
}

void Entity::destroy()
{
    delete this;
}

bool Entity::update()
{
    return false;
}

//-----MovableEntity-----

MovableEntity::MovableEntity(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    maxSpeed(MAXSPEED),
    speedX(0),
    speedY(0)
{}

MovableEntity::~MovableEntity()
{

}

int MovableEntity::getSpeedX() const
{
    return speedX;
}

int MovableEntity::getSpeedY() const
{
    return speedY;
}

void MovableEntity::setSpeed(const int x, const int y)
{
    speedX = x;
    speedY = y;
}

void MovableEntity::changeSpeed(const int x, const int y)
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

bool MovableEntity::move(const int x, const int y)
{
    posX = posX + x;
    posY = posY + y;
    sprite->setPosition(posX, posY);
    return true;
}

//-----TangibleEntity-----

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

TangibleEntity::~TangibleEntity()
{
    delete hitbox;
}
