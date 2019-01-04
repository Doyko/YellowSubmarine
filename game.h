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

class Game
{

public:

    Game(std::string name);
    void loop();
    void menuLoop();
    void drawMenu(int choice, int tick);
    void update();
    void pollEvent();
    void updateView();
    void draw();
    void drawBackground();
    void drawForeground();
    void readEntity(std::string filename);

    sf::RenderWindow window;
    //sf::ContextSettings settings;
    sf::Sprite menu;
    sf::Sprite background;
    sf::Sprite foreground;
    sf::Event event;
    sf::Clock clock;
    sf::View view;
    Map* map;
    Player* player;
};
