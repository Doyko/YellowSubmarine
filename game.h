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

class Game
{

public:

    Game(std::string name);
    void loop();
    void updateView();


    sf::RenderWindow window;
    //sf::ContextSettings settings;
    sf::Texture TextureEntity;
    sf::Texture TextureTile;
    Hitbox HitboxEntity;
    Hitbox HitboxTile;

    sf::Event event;
    sf::Clock clock;
    sf::View view;
    Map* map;
    Player* player;
    TengibleEntity* ball;
};
