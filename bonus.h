#pragma once
#include "player.h"

class Bonus : public TengibleEntity
{
public:
  Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention);
  bool interact(Player* p);
};
