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
    int is(BuffType b);

private:

    T* objet;
    std::map<BuffType, unsigned int> buffMap;

    void invincibility(int i);
    void life(int i);
    void speed(int i);
    void slow(int i);
    void quickfire(int i);
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
            life(it.second);
            break;
        case BuffType::speed :
            speed(it.second);
            break;
        case BuffType::slow :
            slow(it.second);
            break;
        case BuffType::quickfire :
            quickfire(it.second);
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
int Buff<T>::is(BuffType b)
{
    return buffMap[b];
}

template<typename T>
void Buff<T>::life(int i)
{
    static int last;

    if(i != 0 && last == 0)
        objet->addLife(1);

    last = i;
}

template<typename T>
void Buff<T>::speed(int i)
{
    static int last;

    if(i != 0 && last == 0)
        objet->maxSpeed += 10;
    else if(i == 0 && last != 0)
        objet->maxSpeed -= 10;

    last = i;
}

template<typename T>
void Buff<T>::slow(int i)
{
    static int last;

    if(i != 0 && last == 0)
        objet->maxSpeed -= 10;
    else if(i == 0 && last != 0)
        objet->maxSpeed += 10;

    last = i;
}

template<typename T>
void Buff<T>::quickfire(int i)
{

}
