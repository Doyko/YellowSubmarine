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

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Game
{
    public:

    Game(std::string name);
    void loop();


    sf::RenderWindow window;
    //sf::ContextSettings settings;
    sf::Texture TextureEntity;
    sf::Texture TextureTile;
    Hitbox HitboxEntity;

    sf::Event event;
    sf::Clock clock;
    Map* map;
    Player* player;
    TengibleEntity* ball;
};
