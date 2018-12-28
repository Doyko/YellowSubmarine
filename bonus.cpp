#include "bonus.h"

Bonus::Bonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
  TengibleEntity(x, y, m, hb, t, dimention),
  state(0)
{}

//-----LifeBonus-----
LifeBonus::LifeBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
Bonus(x, y, m, hb, t, dimention)
{}

bool LifeBonus::interact(Player* p, sf::RenderWindow& w)
{
    switch (state)
    {
        case 0:
            if(this->checkCollision(p) && p->life < MAXLIFE)
            {
                state = 1;
                p->life++;
                std::cout << "life : " << p->life << std::endl;
            }
            else
                w.draw(*sprite);
            return true;
        default:
            return false;
    }
}

//-----MineBonus-----
MineBonus::MineBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
Bonus(x, y, m, hb, t, dimention)
{}

bool MineBonus::interact(Player* p, sf::RenderWindow& w)
{
    switch (state)
    {
        case 0:
            if(this->checkCollision(p))
            {
                state = 1;
                p->life--;
                std::cout << "life : " << p->life << std::endl;
            }
            else
                w.draw(*sprite);
            return true;
        default:
            return false;
    }
}

//-----SpeedBonus-----
SpeedBonus::SpeedBonus(int x, int y, Map* m, Hitbox& hb, sf::Texture *t, sf::IntRect dimention)
: Entity(x, y, m, t, dimention),
Bonus(x, y, m, hb, t, dimention)
{}

bool SpeedBonus::interact(Player* p, sf::RenderWindow& w)
{
    switch (state)
    {
        case 0:
            if(this->checkCollision(p))
            {
                state = 1;
                p->maxSpeed += 10;
                timer = 500;
            }
            else
                w.draw(*sprite);
            return true;

        case 1:
            if(timer > 0)
                timer--;
            else
            {
                state = 2;
                p->maxSpeed -= 10;
            }
            return true;

        default:
            return false;
    }
}
