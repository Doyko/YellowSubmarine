#include "bonus.h"

Bonus::Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
  TengibleEntity(x, y, m, hb, t, dimention)
{}

bool Bonus::interact(Player* p)
{
    if(p->life < MAXLIFE)
        p->life++;
    std::cout << p->life << std::endl;
    return true;
}
