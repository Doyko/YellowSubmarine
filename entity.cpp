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

bool Entity::move(const int x, const int y)
{
    posX = posX + x;
    posY = posY + y;
    sprite->setPosition(posX + sprite->getOrigin().x, posY + sprite->getOrigin().y);
    return true;
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

//-----TangibleEntity-----

TangibleEntity::TangibleEntity(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    hitbox(new Hitbox(*Data::hitboxEntity, dimension))
{
    hitbox->setPosition(x, y);
}

TangibleEntity::~TangibleEntity()
{
    delete hitbox;
}

bool TangibleEntity::checkCollision(const TangibleEntity* te) const
{
    return hitbox->checkCollision(te->hitbox);
}

bool TangibleEntity::checkCollision(const std::vector<TangibleEntity*> v) const
{
    for(auto & it : v)
    {
        if(hitbox->checkCollision(it->hitbox))
            return true;
    }
    return false;
}

bool TangibleEntity::checkCollisionMap() const

{
    int xmin = hitbox->getLeft();
    int ymin = hitbox->getTop();
    int xmax = xmin + hitbox->getWidth() - 1;
    int ymax = ymin + hitbox->getHeight() - 1;

    if(xmin < 0 || xmax >= Data::map->getNbTileX() * TILE_WIDTH)
        return true;

    if(ymin < 0 || ymax >= Data::map->getNbTileY() * TILE_HEIGHT)
        return true;

    for(int i = xmin/TILE_WIDTH; i <= xmax / TILE_WIDTH; i++)
    {
        for(int j = ymin / TILE_HEIGHT; j <= ymax / TILE_HEIGHT; j++)
        {
            if((*Data::map)(j, i) != NULL && (*Data::map)(j, i)->getTangibility())
            {
                (*Data::map)(j, i)->hitbox->setPosition(i * TILE_WIDTH, j * TILE_HEIGHT);
                if(hitbox->checkCollision((*Data::map)(j, i)->hitbox))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TangibleEntity::move(const int x, const int y)
{
    int moveX = x;
    int moveY = y;
    bool flag = false;
    hitbox->setPosition(posX + moveX, posY);

    while(moveX != 0 && (checkCollisionMap() || checkCollision(Data::explosable)))
    {
        moveX > 0 ? moveX-- : moveX++;
        hitbox->setPosition(posX + moveX, posY);
        flag = true;
    }
    posX = posX + moveX;
    hitbox->setPosition(posX, posY + moveY);

    while(moveY != 0 && (checkCollisionMap() || checkCollision(Data::explosable)))
    {
        moveY > 0 ? moveY-- : moveY++;
        hitbox->setPosition(posX, posY + moveY);
        flag = true;
    }

    posY = posY + moveY;
    sprite->setPosition(posX + sprite->getOrigin().x, posY + sprite->getOrigin().y);
    return flag;
}
