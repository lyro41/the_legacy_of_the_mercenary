#include <SFML/Graphics.hpp>
#include <locale>

int x, y;


int main()
{
    setlocale(LC_ALL,"RUS");

    float CurrentFrame = 0;
    sf::Clock clock;



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
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 1000;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            window.close();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {

            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            heroSprite.setTextureRect(sf::IntRect(96* int(CurrentFrame), 288 ,96, 96));
            heroSprite.move(0, -0.1*time);

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            heroSprite.setTextureRect(sf::IntRect(96* int(CurrentFrame), 0 ,96, 96));
            heroSprite.move(0, 0.1*time);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            heroSprite.setTextureRect(sf::IntRect(96* int(CurrentFrame), 96 ,96, 96));
            heroSprite.move(-0.1*time, 0);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            heroSprite.setTextureRect(sf::IntRect(96* int(CurrentFrame) + 96, 192 ,96, 96));
            heroSprite.move(0.1*time, 0);
        }


        window.clear();

        //time = clock.getElapsedTime().asMilliseconds();
        //clock.restart();

        window.draw(heroSprite);
        window.display();

    }

    return 0;
}
