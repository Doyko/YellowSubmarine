#include "bonus.h"

sf::IntRect Bonus::speedDimension = sf::IntRect(64, 64, 32, 32);
sf::IntRect Bonus::lifeDimension = sf::IntRect(0, 64, 32, 32);
sf::IntRect Bonus::qfDimension = sf::IntRect(160, 160, 32, 32);

Bonus::Bonus(const int x, const int y, buffType t, const sf::IntRect dimension)
:
    Entity(x, y, dimension),
    TangibleEntity(x, y, dimension),
    type(t)
{}

bool Bonus::update()
{
    unsigned int t;
    if(this->checkCollision(Data::player))
    {
        switch(type)
        {
        case buffType::invincibility:
            t = 50;
            break;
        case buffType::life:
            if(Data::player->getLife() < MAXLIFE)
                t = 1;
            else
                return false;
            break;
        case buffType::speed:
            t = 500;
            break;
        case buffType::slow:
            t = 500;
            break;
        case buffType::quickfire:
            t = 500;
            break;
        default:
            break;
        }
        Data::player->addBuff(type, t);
        Data::soundMap["sound/power-up.wav"]->play();
        return true;
    }
    return false;

}
