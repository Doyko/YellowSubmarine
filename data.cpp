#include "data.h"

void Data::init()
{
    if(!Data::textureMenu.loadFromFile("texture/textureMenu.png"))
        exit(1);

    if(!Data::textureEntity.loadFromFile("texture/textureEntity.png"))
        exit(1);

    if(!Data::textureTile.loadFromFile("texture/textureTile.png"))
        exit(1);

    if(!Data::textureBG.loadFromFile("texture/textureBG.png"))
        exit(1);

    if(!Data::textureFG.loadFromFile("texture/textureFG.png"))
        exit(1);

    if(!Data::textureHub.loadFromFile("texture/textureHub.png"))
        exit(1);

    if(!Data::textureMessage.loadFromFile("texture/textureMessage.png"))
        exit(1);
}

void Data::initMap(Map* m)
{
    map = m;
}

void Data::initPlayer(Player* p)
{
    player = p;
}

void Data::clearData()
{
    delete hitboxEntity;
    delete hitboxTile;
}

sf::Texture Data::textureEntity;
sf::Texture Data::textureTile;
sf::Texture Data::textureBG;
sf::Texture Data::textureFG;
sf::Texture Data::textureMenu;
sf::Texture Data::textureHub;
sf::Texture Data::textureMessage;

Hitbox* Data::hitboxEntity = new Hitbox("hitbox/hitboxEntity.pbm");
Hitbox* Data::hitboxTile = new Hitbox("hitbox/hitboxTile.pbm");

std::vector<Entity*> Data::effects;
std::vector<TangibleEntity*> Data::explosable;
std::vector<TangibleEntity*> Data::entities;
std::vector<Bonus*> Data::bonus;

Player* Data::player;

Map* Data::map;

int Data::nbChest = 0;
