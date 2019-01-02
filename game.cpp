#include "game.h"

Game::Game(std::string name)
:
    map(new Map("level.txt")),
    player(new Player(128, 32))
{
    srand(time(NULL));
    Data::initMap(map);
    Data::initPlayer(player);

    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    view.reset(sf::FloatRect(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT));
    //settings.antialiasingLevel = 8;

    background.setTexture(Data::textureBG);
    foreground.setTexture(Data::textureFG);

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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                player->shoot();

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
            update();
            draw();
        }
    }
}

void Game::update()
{
    player->update();

    for(size_t i = 0; i < map->animatedTiles.size(); i++)
        map->animatedTiles[i]->update();

    updateView();

    for(size_t i = 0; i < Data::projectiles.size(); i++)
    {
        if(Data::projectiles[i]->update())
        {
            delete Data::projectiles[i];
            Data::projectiles.erase(Data::projectiles.begin() + i);
            i--;
        }
    }

    for(size_t i = 0; i < Data::mobs.size(); i++)
    {
        if(Data::mobs[i]->update())
        {
            delete Data::mobs[i];
            Data::mobs.erase(Data::mobs.begin() + i);
            i--;
        }
    }

    for(size_t i = 0; i < Data::bonus.size(); i++)
    {
        if(!Data::bonus[i]->interact(player))
        {
            delete Data::bonus[i];
            Data::bonus.erase(Data::bonus.begin() + i);
            i--;
        }
    }
}

void Game::draw()
{
    window.clear(sf::Color(21, 96, 189));
    drawBackground();
    map->draw(window, view);

    for(size_t i = 0; i < Data::projectiles.size(); i++)
    {
        window.draw(*Data::projectiles[i]->sprite);
    }

    for(size_t i = 0; i < Data::mobs.size(); i++)
    {
        window.draw(*Data::mobs[i]->sprite);
    }

    for(size_t i = 0; i < Data::bonus.size(); i++)
    {
        if(Data::bonus[i]->draw)
            window.draw(*Data::bonus[i]->sprite);
    }

    window.draw(*(player->sprite));
    drawForeground();

    window.setView(view);

    window.display();
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

void Game::drawForeground()
{
    float x = - float(view.getCenter().x - WINDOW_HEIGHT / 2) / 2;
    foreground.setPosition(x, background.getPosition().y);

    while(foreground.getPosition().x + foreground.getTextureRect().width < view.getCenter().x - WINDOW_WIDTH / 2)
        foreground.move(foreground.getTextureRect().width, 0);

    for(int i = 0; i < WINDOW_WIDTH / foreground.getTextureRect().width + 1; i++)
    {
        window.draw(foreground);
        foreground.move(foreground.getTextureRect().width, 0);
    }
}

void Game::readEntity(std::string filename)
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
                Data::bonus.push_back(new LifeBonus(x, y));
                break;
            case 'm':
                Data::mobs.push_back(new Mine(x, y));
                break;
            case 's':
                Data::bonus.push_back(new SpeedBonus(x, y));
                break;
            case 'o':
                Data::mobs.push_back(new Octopus(x, y));
                break;
            default:
                break;
        }
    }
}
