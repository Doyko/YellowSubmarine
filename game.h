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
    sf::Texture texture;
    //sf::ContextSettings settings;
    sf::Texture tSubmarine;
    sf::Texture tBloc;
    sf::Sprite sBloc;
    sf::Event event;
    sf::Clock clock;
    Map* map;
    Player* player;
};
