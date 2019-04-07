#include <SFML/Graphics.hpp>
#include <locale>

int x, y;

using namespace sf;

class Сharacter
{
private:


    float x, y, ws, hs, ax, ay, speed;
    int dir = 0;
    String title;
    Image image;
    Texture texture;
    Sprite sprite;


public:


    Character(String f, int X, int Y, float WidthSprite, float HeightSprite)
    {
        title = f;
        ws = WidthSprite;
        hs = HeightSprite;
        image.loadFromFile("images/" + title);
        texture.loadFromImage(image);
        sprite.getTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(ws, hs, ws, hs);
        speed = 0;

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
        case 4:
            ax = 0;
            ay = -speed;
        }

        x += ax*time;
        y += ay*time;

        speed = 0;
        sprite.setPosition(x, y);

    }

    void Set(int Dir)
    {
        dir = Dir;
    }
    void Set(float Speed)
    {
        speed = Speed;
    }
    void Set(Sprite Sprite)
    {
        sprite = Sprite;
    }


};

int main()
{
    setlocale(LC_ALL,"RUS");

    float CurrentFrame = 0;
    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Вертикальная синхронизация

    Character Hero("images/hero.PNG", 100, 960, 96.0, 96.0);


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 1000;


        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            window.close();
        }


        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            Hero.Set(3);
            Hero.Set(0.1);
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            Hero.sprite.setTextureRect(IntRect(96* int(CurrentFrame), 288 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::S))
        {
            Hero.Set(2);
            Hero.Set(0.1);
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            Hero.sprite.setTextureRect(IntRect(0* int(CurrentFrame), 0 ,96, 96));

        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            Hero.Set(1);
            Hero.Set(0.1);
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            Hero.sprite.setTextureRect(IntRect(96* int(CurrentFrame), 96 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::D))
        {
            Hero.Set(0);
            Hero.Set(0.1);
            CurrentFrame += 0,005*time;
            if(CurrentFrame > 3)
                CurrentFrame -= 3;
            Hero.sprite.setTextureRect(IntRect(96* int(CurrentFrame), 192 ,96, 96));

        }

        Hero.Update(time);

        window.clear();

        //time = clock.getElapsedTime().asMilliseconds();
        //clock.restart();

        window.draw(Hero.sprite);
        window.display();

    }

    return 0;
}
