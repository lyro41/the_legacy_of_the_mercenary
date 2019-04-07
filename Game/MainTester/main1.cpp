#include <SFML/Graphics.hpp>
#include <locale>

int x, y;


void update()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        y -= 3;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        y += 3;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        x -= 3;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        x += 3;
    }
}

int main()
{
    setlocale(LC_ALL,"RUS");



    sf::RenderWindow window(sf::VideoMode(1920, 1080), "No game, no life");
    window.setVerticalSyncEnabled(true); // Вертикальная синхронизация

    sf::Texture heroTexture;
    heroTexture.loadFromFile("images/smile.PSD");

    sf::Sprite heroSprite;
    heroSprite.setTexture(heroTexture);
    heroSprite.setPosition(x,y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            update();

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
