#pragma once
#include <map>

enum buffType
{
    life,
    quickfire,
    speed,
    slow,
    invincibility,
    count,
};

template<typename T>
class Buff
{

public:

    Buff(T* t);
    ~Buff();

    void update();
    void addBuff(buffType type, const unsigned int t);
    int getDuration(const buffType type);
    void clear();

    sf::Color* colorEffect[buffType::count];
    bool colorEnable[buffType::count];

private:

    void life();
    void quickfire();
    void speed();
    void slow();
    void invincibility();

    T* objet;
    std::map<buffType, unsigned int> buffMap;
};

template<typename T>
Buff<T>::Buff(T* t)
:
    objet(t)
{
    colorEffect[buffType::life] = NULL;
    colorEffect[buffType::quickfire] = NULL;
    colorEffect[buffType::speed] = new sf::Color(0, 255, 255);
    colorEffect[buffType::slow] = new sf::Color(127, 127, 127);
    colorEffect[buffType::invincibility] = new sf::Color(255, 255, 255, 127);

    for(int i = 0; i < buffType::count; i++)
    {
        colorEnable[i] = false;
    }
}

template<typename T>
Buff<T>::~Buff()
{
    for(int i = 0; i < buffType::count; i++)
    {
        if(colorEffect[i] != NULL)
            delete colorEffect[i];
    }
}

template<typename T>
void Buff<T>::update()
{
    invincibility();
    life();
    speed();
    slow();
    quickfire();
    for(std::map<buffType, unsigned int>::iterator it = buffMap.begin(); it != buffMap.end(); it++)
    {
        if(it->second > 0)
        it->second--;
    }
}

template<typename T>
void Buff<T>::addBuff(buffType type, const unsigned int t)
{
    buffMap[type] += t;
}

template<typename T>
int Buff<T>::getDuration(const buffType type)
{
    return buffMap[type];
}

template<typename T>
void Buff<T>::clear()
{
    for(std::map<buffType, unsigned int>::iterator it = buffMap.begin(); it != buffMap.end(); it++)
    {
        it->second = 0;
    }
    update();
}

template<typename T>
void Buff<T>::invincibility()
{
    static int last;

    if(buffMap[buffType::invincibility] > 0 && last == 0)
    {
        colorEnable[buffType::invincibility] = true;
    }
    else if(buffMap[buffType::invincibility] == 0 && last > 0)
    {
        colorEnable[buffType::invincibility] = false;
    }
    last = buffMap[buffType::invincibility];
}

template<typename T>
void Buff<T>::life()
{
    if(buffMap[buffType::life] != 0)
    {
        objet->addLife(buffMap[buffType::life]);
        buffMap[buffType::life] = 0;
    }
}

template<typename T>
void Buff<T>::speed()
{
    static int last;

    if(buffMap[buffType::speed] > 0 && last == 0)
    {
        colorEnable[buffType::speed] = true;
        objet->maxSpeed += 10;
    }
    else if(buffMap[buffType::speed] == 0 && last > 0)
    {
        colorEnable[buffType::speed] = false;
        objet->maxSpeed -= 10;
    }

    last = buffMap[buffType::speed];
}

template<typename T>
void Buff<T>::slow()
{
    static int last;

    if(buffMap[buffType::slow] > 0 && last == 0)
    {
        objet->maxSpeed -= 10;
        colorEnable[buffType::slow] = true;
    }
    else if(buffMap[buffType::slow] == 0 && last > 0)
    {
        colorEnable[buffType::slow] = false;
        objet->maxSpeed += 10;
    }

    last = buffMap[buffType::slow];
}

template<typename T>
void Buff<T>::quickfire()
{
    if(buffMap[buffType::quickfire] > 0 && objet->getCD() > 50)
        objet->addCD(-50);
}
