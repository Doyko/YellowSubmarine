#include "data.h"

void Data::init()
{
    if(!Data::textureEntity.loadFromFile("texture/textureEntity.png"))
        exit(1);

    if(!Data::textureTile.loadFromFile("texture/textureTile.png"))
        exit(1);

    if(!Data::textureBG.loadFromFile("texture/textureBG.png"))
        exit(1);

    if(!Data::textureFG.loadFromFile("texture/textureFG.png"))
        exit(1);
}

sf::Texture Data::textureEntity;
sf::Texture Data::textureTile;
sf::Texture Data::textureBG;
sf::Texture Data::textureFG;

Hitbox* Data::hitboxEntity = new Hitbox("hitbox/hitboxEntity.pbm");
Hitbox* Data::hitboxTile = new Hitbox("hitbox/hitboxTile.pbm");

sf::IntRect Data::dimPlayer = sf::IntRect(0, 0, 64, 37);
sf::IntRect Data::animPlayerRight = sf::IntRect(0, 0, 64, 37);
sf::IntRect Data::animPlayerLeft = sf::IntRect(256, 0, 64, 37);

sf::IntRect Data::dimTorpedoRight = sf::IntRect(0, 37, 25, 7);
sf::IntRect Data::dimTorpedoLeft = sf::IntRect(0, 44, 25, 7);

sf::IntRect Data::dimExplosion = sf::IntRect(128, 64, 96, 96);

sf::IntRect Data::dimOctopus = sf::IntRect(96, 64, 32, 32);
sf::IntRect Data::spriteOctopusUp = sf::IntRect(96, 96, 32, 32);
sf::IntRect Data::spriteOctopusDown = sf::IntRect(96, 64, 32, 32);

sf::IntRect Data::dimInk = sf::IntRect(64, 96, 32, 32);
