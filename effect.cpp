#include "effect.h"

sf::IntRect Explosion::dimension = sf::IntRect(128, 64, 96, 96);
sf::Vector2f Explosion::speed = sf::Vector2f(0,0);
int Explosion::nbSprite = 5;
int Explosion::animSpeed = 5;

Explosion::Explosion(int x, int y)
:
    Entity(x, y, Explosion::dimension),
    TangibleEntity(x, y, Explosion::dimension),
    animation(new Animation(&Data::textureEntity, Explosion::dimension, Explosion::nbSprite, Explosion::animSpeed)),
    triggered(false)
{}

bool Explosion::update()
{
    if(!triggered)
        trigger();
    if(animation->update())
        return true;
    sprite = animation->currentSprite;
    sprite->setPosition(posX, posY);
    return false;
}

void Explosion::trigger()
{
    if(checkCollision(Data::player))
    {
        Data::player->life--;
        std::cout << "BOOM life = " << Data::player->life << std::endl;
    }

    for(size_t i = 0; i < Data::explosable.size(); i++)
    {
        if(checkCollision(Data::explosable[i]))
        {
            delete Data::explosable[i];
            Data::explosable.erase(Data::explosable.begin() + i);
            i--;
        }
    }

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
        {
            delete Data::entities[i];
            Data::entities.erase(Data::entities.begin() + i);
            i--;
        }
    }
    triggered = true;
}

Explosion::~Explosion()
{

}

sf::IntRect Debris::dimension = sf::IntRect(64, 160, 96, 64);

Debris::Debris(int x, int y)
:
    Entity(x, y, Debris::dimension),
    MovableEntity(x, y, Debris::dimension),
    tick(255)
{}

bool Debris::update()
{
    tick--;
    if(tick == 0)
        return true;
    sprite->setColor(sf::Color(255, 255, 255, tick));
    if(tick % 25 == 0)
        move(0, 1);
    return false;
}

bool Debris::move(int x, int y)
{
    posX = posX + x;
    posY = posY + y;
    sprite->setPosition(posX, posY);
    return true;
}

Debris::~Debris()
{

}

sf::IntRect Bubble::dimension = sf::IntRect(0, 96, 6, 6);
sf::IntRect Bubble::dimSpriteBoop = sf::IntRect(6, 96, 6, 6);

Bubble::Bubble(int x, int y)
:
    Entity(x, y, Bubble::dimension),
    MovableEntity(x, y, Bubble::dimension),
    tick(100)
{
    spriteBoop = new sf::Sprite(Data::textureEntity, Bubble::dimSpriteBoop);
}

bool Bubble::update()
{
    tick--;
    if(tick == 0)
        return true;
    if(tick == 10)
        sprite = spriteBoop;
    if(tick % 10 == 0)
        move(1, -1);
    else if(tick % 10 == 5)
        move(-1 , -1);
    return false;
}

bool Bubble::move(int x, int y)
{
    posX = posX + x;
    posY = posY + y;
    sprite->setPosition(posX, posY);
    return true;
}

Bubble::~Bubble()
{

}

//-----Barricade-----

sf::IntRect Barricade::dimension = sf::IntRect(32, 160, 32, 64);

Barricade::Barricade(int x, int y)
:
    Entity(x, y, Barricade::dimension),
    TangibleEntity(x, y, Barricade::dimension)
{}

Barricade::~Barricade()
{
    Data::effects.push_back(new Debris(posX - 32, posY));
}
