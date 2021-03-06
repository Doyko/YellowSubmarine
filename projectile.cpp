#include "projectile.h"

Projectile::Projectile(const int x, const int y, const sf::IntRect dimension, const sf::Vector2f speed)
:
    Entity(x, y, dimension),
    MovableEntity(x, y, dimension),
    TangibleEntity(x, y, dimension)
{
    speedX = speed.x;
    speedY = speed.y;
}

bool Projectile::update()
{
    return move(speedX, speedY);
}

Projectile::~Projectile()
{

}

//-----Torpedo-----

sf::IntRect Torpedo::dimRight = sf::IntRect(0, 37, 25, 7);
sf::IntRect Torpedo::dimLeft = sf::IntRect(0, 44, 25, 7);
sf::Vector2f Torpedo::speedRight = sf::Vector2f(1, 0);
sf::Vector2f Torpedo::speedLeft = sf::Vector2f(-1, 0);
int Torpedo::nbSprite = 4;
int Torpedo::animSpeed = 4;

Torpedo::Torpedo(const int x, const int y, const sf::IntRect dimension, const sf::Vector2f speed)
:
    Entity(x, y, dimension),
    Projectile(x, y, dimension, speed),
    tick(4)
{
    delete sprite;
    maxSpeed = 20;
    if(speedX > 0)
        animation = new Animation(&Data::textureEntity, Torpedo::dimRight, Torpedo::nbSprite, Torpedo::animSpeed);
    else
        animation = new Animation(&Data::textureEntity, Torpedo::dimLeft, Torpedo::nbSprite, Torpedo::animSpeed);

    sprite = animation->currentSprite;
}

bool Torpedo::update()
{
    if(speedX > 0)
        changeSpeed(ACCELERATION, 0);
    else
        changeSpeed(-ACCELERATION, 0);

    if(animation->update())
        sprite = animation->currentSprite;

    tick--;
    if(tick == 0)
    {
        tick = 4;
        if(speedX > 0)
            Data::effects.push_back(new Bubble(posX, posY));
        else
            Data::effects.push_back(new Bubble(posX + 21, posY));
    }

    for(size_t i = 0; i < Data::explosable.size(); i++)
    {
        if(checkCollision(Data::explosable[i]))
        {
            return true;
        }
    }

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
        {
            return true;
        }
    }
    return move(speedX, speedY);
}

Torpedo::~Torpedo()
{
    Data::effects.push_back(new Explosion(posX - 41, posY - 48));
    delete animation;
    sprite = NULL;
}

//-----Ink-----

sf::IntRect Ink::dimension = sf::IntRect(64, 96, 32, 32);
sf::Vector2f Ink::speed = sf::Vector2f(0, 2);

Ink::Ink(const int x, const int y)
:
    Entity(x, y, Ink::dimension),
    Projectile(x, y, Ink::dimension, Ink::speed)
{}

Ink::~Ink()
{

}

bool Ink::update()
{
    if(checkCollision(Data::player))
    {
        if(Data::player->getLife() != 0)
        {
            Data::player->addLife(-1);
            Data::player->addBuff(buffType::slow, 250);
            if(Data::soundMap["sound/drip.wav"]->getStatus() != sf::SoundSource::Status::Playing)
                Data::soundMap["sound/drip.wav"]->play();
        }
        return true;
    }

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
        {
            Data::entities[i]->destroy();
            Data::entities.erase(Data::entities.begin() + i);
            return true;
        }
    }

    return move(speedX, speedY);
}

//-----Laser-----

sf::IntRect Laser::dimension = sf::IntRect(384, 160, 8, 8);

Laser::Laser(const int x, const int y, const sf::Vector2f s)
:
    Entity(x, y, Laser::dimension),
    Projectile(x, y, Laser::dimension, s)
{}

Laser::~Laser()
{

}

bool Laser::update()
{
    if(checkCollision(Data::player))
    {
        Data::player->addLife(-1);
        return true;
    }

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
        {
            Data::entities[i]->destroy();
            Data::entities.erase(Data::entities.begin() + i);
            return true;
        }
    }

    return move(speedX, speedY);
}
