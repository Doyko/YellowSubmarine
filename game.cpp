#include "game.h"

Game::Game(std::string name)
{
    srand(time(NULL));
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Yellow Submarine");
    window.setVerticalSyncEnabled(true);
    //settings.antialiasingLevel = 8;

    if(!tSubmarine.loadFromFile("Yellow_Submarine_texture.png"))
        exit(1);

    if(!tBloc.loadFromFile("Tile_Texture.png"))
        exit(1);

    sBloc.setTexture(tBloc);
    sBloc.setTextureRect(sf::IntRect(0,0,32,32));
    map = new Map("level.txt", &tBloc);
    player = new Player(128, 128, &tSubmarine, map);
}

void Game::loop()
{
    while(window.isOpen())
    {
        if(clock.getElapsedTime() >= sf::milliseconds(20))
        {
            clock.restart();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player->move(0, -5);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player->move(0, 5);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->move(5, 0);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->move(-5, 0);

            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                }
            }
            window.clear(sf::Color(21, 96, 189));
            map->draw(window);
            window.draw(*(player->sprite));
            window.display();
        }
    }
}
