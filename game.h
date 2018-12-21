#pragma once
#include "param.h"

class Player;

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
    Hitbox HitboxTile;

    sf::Event event;
    sf::Clock clock;
    Map* map;
    Player* player;
};
