#include "bonus.h"

Bonus::Bonus(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
    TengibleEntity(x, y, m, dimention),
    draw(true),
    state(0)
{}

//-----LifeBonus-----
LifeBonus::LifeBonus(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
    Bonus(x, y, m, dimention)
{}

bool LifeBonus::interact(Player* p)
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
            return true;
        default:
            return false;
    }
}

//-----MineBonus-----
MineBonus::MineBonus(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
    Bonus(x, y, m, dimention)
{}

bool MineBonus::interact(Player* p)
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
            return true;
        default:
            return false;
    }
}

//-----SpeedBonus-----
SpeedBonus::SpeedBonus(int x, int y, Map* m, sf::IntRect dimention)
:
    Entity(x, y, m, dimention),
    Bonus(x, y, m, dimention)
{}

bool SpeedBonus::interact(Player* p)
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
            return true;

        case 1:
            draw = false;
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
