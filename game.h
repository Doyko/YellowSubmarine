#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include "player.h"
#include "map.h"
#include "mob.h"
#include "bonus.h"

#define NBLEVEL 3

class Player;
class Bonus;

class Game
{

public:

    Game(const std::string name);
    ~Game();

    void menuLoop();
    void loop();

private:

    void keyEvent();
    void pollEvent();

    void update();
    void updateView();
    template<typename T>
    void updateVector(std::vector<T> &vect) const;

    void menuView();
    void drawMenu(const int choice, const int tick);
    void draw();
    template<typename T>
    void drawVector(const std::vector<T> &vect);
    void drawBackground();
    void drawForeground();
    void drawHub();

    void clearVectors() const;
    template<typename T>
    void clearVector(std::vector<T> &vect) const;
    template<typename T1, typename T2>
    void clearMap(std::map<T1, T2> &map) const;

    void printMessage();
    void nextLevel();
    void printLevel();
    void readEntity(const std::string fileName) const;
    void addEntity(const EntityType e, const int x, const int y, const int p) const;

    void startMusic();

    sf::RenderWindow window;
    sf::Sprite menu;
    sf::Sprite background;
    sf::Sprite foreground;
    sf::Sprite hub;
    sf::Sprite message;
    sf::Event event;
    sf::Clock clock;
    sf::View view;
    sf::Music menuMusic;
    sf::Music levelMusic;
    sf::Music atmosphere;
    Map* map;
    Player* player;

    int level;
};


template<typename T>
void Game::updateVector(std::vector<T> &vect) const
{
    for(size_t i = 0; i < vect.size(); i++)
    {
        if(vect[i]->update())
        {
            vect[i]->destroy();
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
    vect.clear();
}

template<typename T1, typename T2>
void Game::clearMap(std::map<T1, T2> &map) const
{
    for(auto& i : map)
    {
        delete i.second;
    }
    map.clear();
}
