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

class Player;
class Bonus;

class Game
{

public:

    Game(const std::string name);
    void loop();

private:

    void menuLoop();
    void drawMenu(const int choice, const int tick);

    void update();
    void pollEvent();
    void updateView();
    template<typename T>
    void updateVector(std::vector<T> &vect);
    void updateVector(std::vector<Bonus*> &vect);

    void draw();
    template<typename T>
    void drawVector(const std::vector<T> &vect);
    void drawVector(const std::vector<Bonus*> &vect);
    void drawBackground();
    void drawForeground();
    void drawHub();

    void printMessage();
    void readEntity(const std::string filename) const;
    void addEntity(const int x, const int y, const int idEntity) const;

    enum stateEnum{play, win, death};

    sf::RenderWindow window;
    //sf::ContextSettings settings;
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

    stateEnum state;
};


template<typename T>
void Game::updateVector(std::vector<T> &vect)
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
