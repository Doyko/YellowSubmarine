#pragma once
#include "player.h"
#include "buff.h"

class Player;

class Bonus : public TangibleEntity
{

public:

    Bonus(const int x, const int y, buffType t, const sf::IntRect dimension);
    bool update();

    static sf::IntRect lifeDimension;
    static sf::IntRect speedDimension;
    static sf::IntRect qfDimension;

private:

    buffType type;
};
