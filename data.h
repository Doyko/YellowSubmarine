#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "hitbox.h"
#include "entity.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define MAXLIFE 3
#define COOLDOWN 100
#define MAXSPEED 20

class Hitbox;
class Entity;
class TangibleEntity;
class Map;
class Player;
class Bonus;
class Mob;

enum gameState{play, win, death, end};

class Data
{

public:


    static void init();
    static void initMap(Map* m);
    static void initPlayer(Player* p);
    static void clearData();

    static sf::Texture textureMenu;
    static sf::Texture textureEntity;
    static sf::Texture textureTile;
    static sf::Texture textureBG;
    static sf::Texture textureFG;
    static sf::Texture textureHub;
    static sf::Texture textureMessage;

    static std::vector<std::string> soundList;
    static std::map<std::string, sf::Sound*> soundMap;
    static std::vector<sf::SoundBuffer*> soundBuffers;

    static Hitbox* hitboxEntity;
    static Hitbox* hitboxTile;

    static std::vector<Entity*> effects;
    static std::vector<TangibleEntity*> explosable;
    static std::vector<Mob*> entities;
    static std::vector<Bonus*> bonus;

    static Player* player;

    static Map* map;

    static int nbChest;
    static gameState state;
};
