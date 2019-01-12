#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include "data.h"
#include "player.h"
#include "map.h"
#include "entity.h"
#include "mob.h"
#include "projectile.h"
#include "bonus.h"

#define NBLEVEL 1

class Player;
class Bonus;

class Game
{

public:

    Game(const std::string name);
    void menuLoop();
    void loop();
    ~Game();

private:

    void drawMenu(const int choice, const int tick);

    void update();
    void keyEvent();
    void pollEvent();
    void updateView();
    template<typename T>
    void updateVector(std::vector<T> &vect) const;
    void updateVector(std::vector<Bonus*> &vect) const;

    void draw();
    template<typename T>
    void drawVector(const std::vector<T> &vect);
    void drawVector(const std::vector<Bonus*> &vect);
    void drawBackground();
    void drawForeground();
    void drawHub();

    void clearVectors() const;
    template<typename T>
    void clearVector(std::vector<T> &vect) const;

    void printMessage();
    void readEntity(const std::string fileName) const;
    void addEntity(const int x, const int y, const int idEntity) const;

    enum stateEnum{play, win, death};

    sf::RenderWindow window;
    sf::Sprite menu;
    sf::Sprite background;
    sf::Sprite foreground;
    sf::Sprite hub;
    sf::Sprite message;
    sf::Event event;
    sf::Clock clock;
    sf::View view;
    Map* map;
    Player* player;

    int level;
    stateEnum state;
};


template<typename T>
void Game::updateVector(std::vector<T> &vect) const
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        if(vect[i]->update())
        {
            delete vect[i];
            vect.erase(vect.begin() + i);
            i--;
        }
    }
}

template<typename T>
void Game::drawVector(const std::vector<T> &vect)
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        window.draw(*vect[i]->sprite);
    }
}

template<typename T>
void Game::clearVector(std::vector<T> &vect) const
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        delete vect[i];
    }
}
