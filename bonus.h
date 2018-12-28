#pragma once
#include "player.h"

class Bonus : public TengibleEntity
{
public:
    Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    virtual bool interact(Player* p) = 0;
    //return true if the bonus is still usable. return false if the bonus is useless and should be destroy

protected:
    int state;
};

class LifeBonus : public Bonus
{
public:
    LifeBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    virtual bool interact(Player* p);
};

class MineBonus : public Bonus
{
public:
    MineBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    virtual bool interact(Player* p);
};

class SpeedBonus : public Bonus
{
public:
    SpeedBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
    virtual bool interact(Player* p);

private:
    int timer;
};
