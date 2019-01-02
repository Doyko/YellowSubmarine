#pragma once
#include "player.h"

class Player;

class Bonus : public TengibleEntity
{
public:
    Bonus(int x, int y, sf::IntRect dimension);
    virtual bool interact(Player* p) = 0;
    //return true if the bonus is still usable. return false if the bonus is useless and should be destroy

    bool draw;

protected:
    int state;
};

class LifeBonus : public Bonus
{
public:
    LifeBonus(int x, int y);
    virtual bool interact(Player* p);

    static sf::IntRect dimension;
};

class SpeedBonus : public Bonus
{
public:
    SpeedBonus(int x, int y);
    virtual bool interact(Player* p);

    static sf::IntRect dimension;

private:
    int timer;
};
