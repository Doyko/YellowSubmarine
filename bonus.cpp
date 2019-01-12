#include "bonus.h"

sf::IntRect Bonus::speedDimension = sf::IntRect(64, 64, 32, 32);
sf::IntRect Bonus::lifeDimension = sf::IntRect(0, 64, 32, 32);

Bonus::Bonus(const int x, const int y, BuffType t, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    TangibleEntity(x, y, dimension),
    type(t)
{}

bool Bonus::interact()
{

    if(this->checkCollision(Data::player))
    {
        Data::player->addBuff(type, 500);
        return false;
    }
    return true;

}
