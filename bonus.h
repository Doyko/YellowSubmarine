#pragma once
#include "player.h"

class Player;

class Bonus : public TangibleEntity
{

public:

    Bonus(const int x, const int y, const sf::IntRect dimension);
    virtual bool interact(Player* p) = 0;
    //return true if the bonus is still usable. return false if the bonus is useless and should be destroy

    bool draw;

protected:

    int state;
};

class LifeBonus : public Bonus
{

public:

    LifeBonus(const int x, const int y);
    virtual bool interact(Player* p);

    static sf::IntRect dimension;
};

class SpeedBonus : public Bonus
{

public:

    SpeedBonus(const int x, const int y);
    virtual bool interact(Player* p);

    static sf::IntRect dimension;

private:
    int timer;
};
