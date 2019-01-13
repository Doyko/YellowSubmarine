#pragma once
#include "player.h"
#include "buff.h"

class Player;

class Bonus : public TangibleEntity
{

public:

    Bonus(const int x, const int y, BuffType t, const sf::IntRect dimension);
    bool interact(); //return true if the bonus is still usable. return false if the bonus is useless and should be destroy

    static sf::IntRect lifeDimension;
    static sf::IntRect speedDimension;
    static sf::IntRect qfDimension;

private:

    BuffType type;
};
