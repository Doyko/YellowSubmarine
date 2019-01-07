#include "bonus.h"

Bonus::Bonus(const int x, const int y, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    TangibleEntity(x, y, dimension),
    draw(true),
    state(0)
{}

//-----LifeBonus-----

sf::IntRect LifeBonus::dimension = sf::IntRect(0, 64, 32, 32);

LifeBonus::LifeBonus(const int x, const int y)
:
    Entity(x, y, dimension),
    Bonus(x, y, dimension)
{}

bool LifeBonus::interact()
{
    switch (state)
    {
        case 0:
            if(this->checkCollision(Data::player) && Data::player->getLife() < MAXLIFE)
            {
                state = 1;
                Data::player->addLife(1);
            }
            return true;

        default:
            return false;
    }
}

//-----SpeedBonus-----

sf::IntRect SpeedBonus::dimension = sf::IntRect(64, 64, 32, 32);

SpeedBonus::SpeedBonus(const int x, const int y)
:
    Entity(x, y, dimension),
    Bonus(x, y, dimension)
{}

bool SpeedBonus::interact()
{
    switch (state)
    {
        case 0:
            if(this->checkCollision(Data::player))
            {
                state = 1;
                Data::player->maxSpeed += 10;
                timer = 500;
            }
            return true;

        case 1:
            draw = false;
            if(timer > 0)
                timer--;
            else
            {
                state = 2;
                Data::player->maxSpeed -= 10;
            }
            return true;

        default:
            return false;
    }
}
