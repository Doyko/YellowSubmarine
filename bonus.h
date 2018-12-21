#pragma once
#include "param.h"

class Player;

class Bonus : public InteractiveEntity
{
public:
  Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
  bool interact(InteractiveEntity* ie);
  bool interact(Player* p);
};
