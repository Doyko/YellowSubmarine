#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include "player.h"
#include "param.h"
#include "map.h"
#include "entity.h"
#include "bonus.h"
#include "texture.h"

class Game
{

public:

    Game(std::string name);
    void loop();
    void updateView();
    void draw();
    void drawBackground();
    void drawForeground();
    void readEntity(std::string filename);

    sf::RenderWindow window;
    //sf::ContextSettings settings;
    sf::Sprite background;
    sf::Sprite foreground;
    sf::Event event;
    sf::Clock clock;
    sf::View view;
    Map* map;
    Player* player;
    std::vector<Bonus*> bonus;
    std::vector<Projectile*> projectiles;
};
