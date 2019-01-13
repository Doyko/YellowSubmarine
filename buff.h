#pragma once
#include <map>
#include <iostream>
#include "data.h"

enum BuffType
{
    invincibility,
    life,
    speed,
    slow,
    quickfire,
};

template<typename T>
class Buff
{

public:

    Buff(T* t);

    void update();
    void addBuff(BuffType b, unsigned int t);
    int duration(BuffType b);

private:

    T* objet;
    std::map<BuffType, unsigned int> buffMap;

    void life();
    void speed();
    void slow();
    void quickfire();
};

template<typename T>
Buff<T>::Buff(T* t)
:
    objet(t)
{}

template<typename T>
void Buff<T>::update()
{
    for(auto & it : buffMap)
    {
        if(it.second > 0)
            it.second--;

        switch (it.first)
        {
        case BuffType::life :
            life();
            break;
        case BuffType::speed :
            speed();
            break;
        case BuffType::slow :
            slow();
            break;
        case BuffType::quickfire :
            quickfire();
            break;
        default:
            break;
        }
    }
}

template<typename T>
void Buff<T>::addBuff(BuffType b, unsigned int t)
{
    buffMap[b] += t;
}

template<typename T>
int Buff<T>::duration(BuffType b)
{
    return buffMap[b];
}

template<typename T>
void Buff<T>::life()
{
    if(buffMap[BuffType::life] != 0)
        objet->addLife(1);
}

template<typename T>
void Buff<T>::speed()
{
    static int last;

    if(buffMap[BuffType::speed] > 0 && last == 0)
        objet->maxSpeed += 10;
    else if(buffMap[BuffType::speed] == 0 && last > 0)
        objet->maxSpeed -= 10;

    last = buffMap[BuffType::speed];
}

template<typename T>
void Buff<T>::slow()
{
    static int last;

    if(buffMap[BuffType::slow] > 0 && last == 0)
        objet->maxSpeed -= 10;
    else if(buffMap[BuffType::slow] == 0 && last > 0)
        objet->maxSpeed += 10;

    last = buffMap[BuffType::slow];
}

template<typename T>
void Buff<T>::quickfire()
{
    if(buffMap[BuffType::quickfire] > 0 && objet->getCD() > 50)
        objet->addCD(-50);
}
