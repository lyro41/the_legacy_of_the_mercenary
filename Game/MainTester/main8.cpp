#include <SFML/Graphics.hpp>
#include <locale>

int x, y;

using namespace sf;

class Character
{

private:


    float x, y, ws, hs, ax, ay, speed;
    int dir = 0;
    String title;
    Image image;
    Texture texture;
    Sprite sprite;
    float CurrentFrame = 0;


public:


    Character(String f, int X, int Y, float WidthSprite, float HeightSprite, float Speed)
    {
        title = f;
        ws = WidthSprite;
        hs = HeightSprite;
        image.loadFromFile("images/" + title);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(ws, hs, ws, hs));
        speed = Speed;

    }

    void Update(float time)
    {
        switch (dir)
        {
        case 0:
            ax = speed;
            ay = 0;
        case 1:
            ax = -speed;
            ay = 0;
        case 2:
            ax = 0;
            ay = speed;
        case 3:
            ax = 0;
            ay = -speed;
        }

        x += ax*time;
        y += ay*time;

        speed = 0;
        sprite.setPosition(x, y);

    }

    void Move(float time)
    {

        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = 3;
            CurrentFrame += (0,005*time);
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96* int(CurrentFrame), 288 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = 2;
            CurrentFrame += (0,005*time);
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(0* int(CurrentFrame), 0 ,96, 96));

        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = 1;
            CurrentFrame += (0,005*time);
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96* int(CurrentFrame), 96 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = 0;
            CurrentFrame += (0,005*time);
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            sprite.setTextureRect(IntRect(96* int(CurrentFrame), 192 ,96, 96));

        }
    }

    void getSprite()
    {

    }

};

int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Вертикальная синхронизация

    Character Hero("images/hero.PNG", 100, 960, 96.0, 96.0, 0.1);


    while (window.isOpen())
    {
        float Time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        Time /= 1000;


        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            window.close();
        }

        Hero.Move(Time);
        Hero.Update(Time);


        window.clear();

        //time = clock.getElapsedTime().asMilliseconds();
        //clock.restart();

        window.draw();
        window.display();

    }

    return 0;
}
