#include "bonus.h"

Bonus::Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
  InteractiveEntity(x, y, m, hb, t, dimention)
{}

bool Bonus::interact(InteractiveEntity* ie)
{
  if(dynamic_cast<Player*>(ie) == NULL)
  {
    return false;
  }
  else
  {
    return interact(ie);
  }
}

bool Bonus::interact(Player* p)
{
  p->life++;
  return true;
}
