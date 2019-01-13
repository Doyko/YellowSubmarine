#include "bonus.h"

sf::IntRect Bonus::speedDimension = sf::IntRect(64, 64, 32, 32);
sf::IntRect Bonus::lifeDimension = sf::IntRect(0, 64, 32, 32);
sf::IntRect Bonus::qfDimension = sf::IntRect(160, 160, 32, 32);

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
        switch(type)
        {
        case BuffType::invincibility:
            Data::player->addBuff(type, 50);
            break;
        case BuffType::life:
            if(Data::player->getLife() < MAXLIFE)
                Data::player->addBuff(type, 2);
            else
                return true;
            break;
        case BuffType::speed:
            Data::player->addBuff(type, 500);
            break;
        case BuffType::slow:
            Data::player->addBuff(type, 500);
            break;
        case BuffType::quickfire:
            Data::player->addBuff(type, 500);
            break;
        default:
            break;
        }
        return false;
    }
    return true;

}
