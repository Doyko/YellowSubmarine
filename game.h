#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "player.h"
#include "param.h"
#include "map.h"
#include "entity.h"
#include "bonus.h"

class Game
{

public:

    Game(std::string name);
    void loop();
    void updateView();
    void drawBackground();

    sf::RenderWindow window;
    //sf::ContextSettings settings;
    sf::Texture textureEntity;
    sf::Texture textureTile;
    sf::Texture textureBG;
    Hitbox HitboxEntity;
    Hitbox HitboxTile;
    sf::Sprite background;
    sf::Event event;
    sf::Clock clock;
    sf::View view;
    Map* map;
    Player* player;
    Bonus* heart;
};
