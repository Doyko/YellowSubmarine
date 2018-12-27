#include "game.h"

Game::Game(std::string name)
:
    HitboxEntity(Hitbox("HitboxEntity.pbm")),
    HitboxTile(Hitbox("HitboxTile.pbm")),
    map(new Map("level.txt", &textureTile, HitboxTile)),
    player(new Player(32, 32, map, HitboxEntity, &textureEntity, sf::IntRect(0,0,64,37)))
{
    srand(time(NULL));
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT));
    //settings.antialiasingLevel = 8;

    if(!textureEntity.loadFromFile("TextureEntity.png"))
        exit(1);

    if(!textureTile.loadFromFile("TextureTile.png"))
        exit(1);

    if(!textureBG.loadFromFile("TextureBG.png"))
        exit(1);

    background.setTexture(textureBG);

    readEntity("Entity.txt");
}

void Game::loop()
{
    while(window.isOpen())
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player->changeSpeed(0, -ACCELERATION);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player->changeSpeed(0, ACCELERATION);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->changeSpeed(ACCELERATION, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->changeSpeed(-ACCELERATION, 0);

            player->update();
            for(size_t i = 0; i < map->animatedTiles.size(); i++)
                map->animatedTiles[i]->update();
            updateView();

            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    default :
                        break;
                }
            }
            window.clear(sf::Color(21, 96, 189));
            drawBackground();
            map->draw(window, view);
            window.draw(*(player->sprite));

            for(std::vector<Bonus*>::iterator i = vbonus.begin(); i != vbonus.end(); i++)
            {
                if(player->checkCollision(*i))
                {
                    (*i)->interact(player);
                    (*i)->~Bonus();
                    vbonus.erase(i);
                    break;
                }
                window.draw(*((*i)->sprite));
            }

            window.setView(view);
            window.display();
        }
    }
}

void Game::updateView()
{
    int x;
    int y;

    if(player->posX < WINDOW_WIDTH / 2)
        x = WINDOW_WIDTH / 2;
    else if(player->posX > map->nbTileX * TILE_WIDTH - WINDOW_WIDTH / 2)
        x = map->nbTileX * TILE_WIDTH - WINDOW_WIDTH / 2;
    else
        x = player->posX;

    if(player->posY < WINDOW_HEIGHT / 2)
        y = WINDOW_HEIGHT / 2;
    else if(player->posY > map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT / 2)
        y = map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT / 2;
    else
        y = player->posY;

    view.setCenter(x, y);
}

void Game::drawBackground()
{
    float y = float(view.getCenter().y - WINDOW_HEIGHT / 2) / (map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT);
    float x = float(view.getCenter().x - WINDOW_HEIGHT / 2) / (map->nbTileY * TILE_HEIGHT - WINDOW_HEIGHT);
    background.setPosition(x * (map->nbTileY * TILE_HEIGHT - background.getTextureRect().height) - background.getTextureRect().width, y * (map->nbTileY * TILE_HEIGHT - background.getTextureRect().height));

    while(background.getPosition().x + background.getTextureRect().width < view.getCenter().x - WINDOW_WIDTH / 2)
        background.move(background.getTextureRect().width, 0);

    for(int i = 0; i < WINDOW_WIDTH / background.getTextureRect().width + 1; i++)
    {
        window.draw(background);
        background.move(background.getTextureRect().width, 0);
    }
}

void Game::readEntity(const char * filename)
{
    std::ifstream ifs(filename);
    int nbBonus, x, y;
    char type;

    ifs >> nbBonus;

    for(int i = 0 ; i < nbBonus ; i++)
    {
        ifs >> type;
        ifs >> x;
        ifs >> y;
        switch (type)
        {
            case 'l':
                vbonus.push_back(new LifeBonus(x, y, map, HitboxEntity, &textureEntity, sf::IntRect(0,64,32,96)));
                break;
            case 'm':
                vbonus.push_back(new MineBonus(x, y, map, HitboxEntity, &textureEntity, sf::IntRect(32,64,64,96)));
                break;

            default:
                break;
        }

    }
}
