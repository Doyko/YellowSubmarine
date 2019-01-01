#pragma once
#include <SFML/Graphics.hpp>
#include "hitbox.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Hitbox;

class Data
{

public:

    static void init();

    static sf::Texture textureEntity;
    static sf::Texture textureTile;
    static sf::Texture textureBG;
    static sf::Texture textureFG;

    static Hitbox* hitboxEntity;
    static Hitbox* hitboxTile;

    static sf::IntRect dimPlayer;
    static sf::IntRect animPlayerRight;
    static sf::IntRect animPlayerLeft;

    static sf::IntRect dimTorpedoRight;
    static sf::IntRect dimTorpedoLeft;

    static sf::IntRect dimExplosion;
    
    static sf::IntRect dimOctopus;
    static sf::IntRect spriteOctopusUp;
    static sf::IntRect spriteOctopusDown;

    static sf::IntRect dimInk;
};
