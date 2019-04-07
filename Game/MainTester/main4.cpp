#include <SFML/Graphics.hpp>
#include <locale>

int x, y;


int main()
{
    setlocale(LC_ALL,"RUS");



    sf::RenderWindow window(sf::VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Вертикальная синхронизация



    sf::Texture heroTexture;
    heroTexture.loadFromFile("images/hero.PNG");

    sf::Sprite heroSprite;
    heroSprite.setTexture(heroTexture);
    heroSprite.setTextureRect(sf::IntRect(0, 192 ,96, 96));
    heroSprite.setPosition(x,y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                heroSprite.setTextureRect(sf::IntRect(0, 288 ,96, 96));
                y -= 3;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                heroSprite.setTextureRect(sf::IntRect(0, 0 ,96, 96));
                y += 3;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                heroSprite.setTextureRect(sf::IntRect(96, 192 ,-96, 96));
                x -= 3;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                heroSprite.setTextureRect(sf::IntRect(0, 192 ,96, 96));
                x += 3;
            }

        }
        window.clear();
        heroSprite.setPosition(x,y);

        //time = clock.getElapsedTime().asMilliseconds();
        //clock.restart();

        window.draw(heroSprite);
        window.display();

    }

    return 0;
}
