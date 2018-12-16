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

    if(!tBall.loadFromFile("ball.png"))
        exit(1);

    sBloc.setTexture(tBloc);
    sBloc.setTextureRect(sf::IntRect(0,0,32,32));
    map = new Map("level.txt", &tBloc);
    player = new Player(128, 128, map, &tSubmarine, sf::IntRect(0,0,64,37));
    ball = new TengibleEntity(1024, 448, map, &tBall, sf::IntRect(0,0,32,32), new Hitbox("ball.pbm"));

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
            map->draw(window);
            window.draw(*(player->sprite));
            if(!player->checkCollision(ball))
                window.draw(*(ball->sprite));
            window.display();
        }
    }
}
