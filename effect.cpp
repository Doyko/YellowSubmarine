#include "effect.h"

sf::IntRect Explosion::dimension = sf::IntRect(128, 64, 96, 96);
int Explosion::nbSprite = 5;
int Explosion::animSpeed = 5;

Explosion::Explosion(const int x, const int y)
:
    Entity(x, y, Explosion::dimension),
    TangibleEntity(x, y, Explosion::dimension),
    animation(new Animation(&Data::textureEntity, Explosion::dimension, Explosion::nbSprite, Explosion::animSpeed)),
    triggered(false)
{
    delete sprite;
    sprite = animation->currentSprite;
}

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
        if(Data::player->getLife() != 0)
            Data::player->addLife(-1);
    }

    for(size_t i = 0; i < Data::explosable.size(); i++)
    {
        if(checkCollision(Data::explosable[i]))
        {
            Data::explosable[i]->destroy();
            Data::explosable.erase(Data::explosable.begin() + i);
            i--;
        }
    }

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
        {
            Data::entities[i]->destroy();
            Data::entities.erase(Data::entities.begin() + i);
            i--;
        }
    }

    triggered = true;
}

Explosion::~Explosion()
{
    delete animation;
    sprite = NULL;
}

//-----Barricade-----

sf::IntRect Barricade::dimension = sf::IntRect(32, 160, 32, 64);

Barricade::Barricade(const int x, const int y)
:
    Entity(x, y, Barricade::dimension),
    TangibleEntity(x, y, Barricade::dimension)
{}

Barricade::~Barricade()
{

}

void Barricade::destroy()
{
    Data::effects.push_back(new Debris(posX - 32, posY));
    delete this;
}

//-----Debris-----

sf::IntRect Debris::dimension = sf::IntRect(64, 160, 96, 64);

Debris::Debris(const int x, const int y)
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

Debris::~Debris()
{

}

//-----Bubble-----

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
    {
        delete sprite;
        sprite = spriteBoop;
    }

    if(tick % 10 == 0)
        move(1, -1);
    else if(tick % 10 == 5)
        move(-1 , -1);

    return false;
}

Bubble::~Bubble()
{

}

//-----Corpse-----

sf::IntRect Corpse::octopus = sf::IntRect(64, 256, 32, 32);
sf::IntRect Corpse::shark = sf::IntRect(0, 256, 64, 32);
sf::IntRect Corpse::jellyfish = sf::IntRect(320, 160, 32, 64);

Corpse::Corpse(const int x, const int y, sf::IntRect dimension)
:
    Entity(x, y, dimension),
    MovableEntity(x, y, dimension),
    TangibleEntity(x, y, dimension),
    tick(255),
    snare(false)
{}

bool Corpse::update()
{
    tick--;

    if(tick == 0)
        return true;

    sprite->setColor(sf::Color(255, 255, 255, tick));

    if(tick % 5 == 0)
    {
        if(snare == false)
        {
            snare = move(0, -1);
        }
    }

    return false;
}

bool Corpse::move(const int x, const int y)
{
    int moveX = x;
    int moveY = y;
    bool flag = false;

    while(moveX != 0 && hitbox->checkCollision(posX + moveX, posY))
    {
        moveX > 0 ? moveX-- : moveX++;
        flag = true;
    }
    posX = posX + moveX;

    while(moveY != 0 && hitbox->checkCollision(posX, posY + moveY))
    {
        moveY > 0 ? moveY-- : moveY++;
        flag = true;
    }

    posY = posY + moveY;
    sprite->setPosition(posX, posY);
    return flag;
}

Corpse::~Corpse()
{

}
//-----Chest-----

sf::IntRect Chest::dimension = sf::IntRect(64, 128, 32, 32);
sf::IntRect Chest::dimSpriteOpen = sf::IntRect(96, 128, 32, 32);

Chest::Chest(const int x, const int y)
:
    Entity(x, y, Chest::dimension),
    TangibleEntity(x, y, Chest::dimension),
    open(false)
{

}

bool Chest::update()
{
    if(open == false)
    {
        if(checkCollision(Data::player))
        {
            Data::nbChest--;
            open = true;
            delete sprite;
            sprite = new sf::Sprite(Data::textureEntity, Chest::dimSpriteOpen);
            sprite->setPosition(posX, posY);
        }
    }
    return false;
}

Chest::~Chest()
{
}

//-----Current-----
sf::IntRect Current::dimension = sf::IntRect(0, 288, 32, 32);
int Current::nbSprite = 4;
int Current::animSpeed = 5;

Current::Current(const int x, const int y, const int dir)
:
    Entity(x, y, Current::dimension),
    TangibleEntity(x, y, Current::dimension),
    animation(NULL),
    direction(dir)
{
    if(direction < 0 || direction > 3)
        direction = 0;

    dimension.left = 128 * direction;
    delete sprite;
    animation = new Animation(&Data::textureEntity, Current::dimension, Current::nbSprite, Current::animSpeed);
    animation->setPosition(x, y);
    sprite = animation->currentSprite;
}

Current::~Current()
{
    delete animation;
    sprite = NULL;
}

bool Current::update()
{
    animation->update();
    sprite = animation->currentSprite;

    if(checkCollision(Data::player))
        moveEntity(Data::player);

    for(size_t i = 0; i < Data::entities.size(); i++)
    {
        if(checkCollision(Data::entities[i]))
            moveEntity(Data::entities[i]);
    }

    return false;
}

void Current::moveEntity(MovableEntity* me)
{
    switch (direction)
    {
        case 0:
            me->move(0,-1);
            break;
        case 1:
            me->move(0,1);
            break;
        case 2:
            me->move(-1,0);
            break;
        case 3:
            me->move(1,0);
            break;
        default:
            break;
    }
}
