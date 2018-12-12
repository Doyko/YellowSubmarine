#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "entity.h"
#include "param.h"

#include <stdlib.h>
#include <time.h>

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
    Entity* player;
};
