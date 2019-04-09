#include <SFML/Graphics.hpp>
#include <locale>
#include "map.h"
#include "view.h"
#include "object.h"


using namespace sf;

class Character
{

private:


    float x, y, ws, hs, ax, ay, speed, original_speed;
    int dir = 0;
    Image image;
    Texture texture;
    Sprite sprite;
    float current_frame = 0;


public:


    Character(String title_pers, int X, int Y, float width_sprite, float height_sprite, float Speed)
    {
        ws = width_sprite;
        hs = height_sprite;
        image.loadFromFile("images/" + title_pers);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X;
        y = Y;
        sprite.setTextureRect(IntRect(ws, hs, ws, hs));
        original_speed = Speed;
        sprite.setPosition(x, y);

    }

    void Update(float time)
    {
        if(Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = 3;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 3)
                current_frame = 0;
            sprite.setTextureRect(IntRect(96* int(current_frame), 288 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = 2;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 3)
                current_frame = 0;
            sprite.setTextureRect(IntRect(96* int(current_frame), 0 ,96, 96));

        }
        if(Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = 1;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 3)
                current_frame = 0;
            sprite.setTextureRect(IntRect(96* int(current_frame), 96 ,96, 96));

        }
        else if(Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = 0;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 3)
                current_frame = 0;
            sprite.setTextureRect(IntRect(96* int(current_frame), 192 ,96, 96));

        }

        getCharacterCoordinateView(this->getCharacterCoordinateX(), this->getCharacterCoordinateY());

        switch (dir)
        {
        case 0:
            ax = speed;
            ay = 0;
            break;
        case 1:
            ax = -speed;
            ay = 0;
            break;
        case 2:
            ax = 0;
            ay = speed;
            break;
        case 3:
            ax = 0;
            ay = -speed;
            break;
        }

        x += ax*time;
        y += ay*time;

        speed = 0;

        sprite.setPosition(x, y);
        //this->interactionWithMap();

    }

    float getCharacterCoordinateX()
    {
        return x;
    }

    float getCharacterCoordinateY()
    {
        return y;
    }

    Sprite getSprite()
    {
        return sprite;
    }

    void interactionWithMap()
    {
        for(int i = y / 32; i < (y + hs) / 32; ++i)
            for(int j = x / 32; j < (x + ws) / 32; ++j)
            {
                if(titleMap[i][j] == '0')
                {

                    if(ay > 0)
                    {
                        y = i * 32 - hs;
                    }
                    else if(ay < 0)
                    {
                        y = i * 32 + 32;
                    }
                    else if(ax > 0)
                    {
                        x = j * 32 - ws;
                    }
                    else if(ax < 0)
                    {
                        x = j * 32 + 32;
                    }

                }

                if(titleMap[i][j] == 's')
                {
                    titleMap[i][j] = ' ';
                }

            }

    }

};



class Map
{

private:

    Image map_image;
    Texture map_texture;
    Sprite map_sprite;

    Image grass_image;
    Texture grass_texture;
    Sprite grass_sprite;

public:

    Map(String title_map, String title_grass)
    {
        map_image.loadFromFile("images/"+title_map);
        map_texture.loadFromImage(map_image);
        map_sprite.setTexture(map_texture);

        grass_image.loadFromFile("images/"+title_grass);
        grass_texture.loadFromImage(grass_image);
        grass_sprite.setTexture(grass_texture);
    }

    Sprite DrawMap(RenderWindow &window)
    {
        for(int i = 0; i < height_map; ++i)
            for(int j = 0; j < width_map; ++j)
            {
                if(titleMap[i][j] == ' ')
                    map_sprite.setTextureRect(IntRect(0, 0, 64, 64));
                else if (titleMap[i][j] == 'a')
                    map_sprite.setTextureRect(IntRect(64, 0, 64, 64));
                else if (titleMap[i][j] == 'b')
                    map_sprite.setTextureRect(IntRect(64 * 2, 0, 64, 64));
                else if (titleMap[i][j] == 'c')
                    map_sprite.setTextureRect(IntRect(64 * 3, 0, 64, 64));
                else if (titleMap[i][j] == 'd')
                    map_sprite.setTextureRect(IntRect(64 * 4, 0, 64, 64));
                else if (titleMap[i][j] == 'e')
                    map_sprite.setTextureRect(IntRect(64 * 5, 0, 64, 64));
                else if (titleMap[i][j] == 'f')
                    map_sprite.setTextureRect(IntRect(64 * 6, 0, 64, 64));
                else if (titleMap[i][j] == 'g')
                    map_sprite.setTextureRect(IntRect(64 * 7, 0, 64, 64));
                else if (titleMap[i][j] == 'h')
                    map_sprite.setTextureRect(IntRect(64 * 8, 0, 64, 64));
                else if (titleMap[i][j] == 'i')
                    map_sprite.setTextureRect(IntRect(64 * 9, 0, 64, 64));
                else if (titleMap[i][j] == 'j')
                    map_sprite.setTextureRect(IntRect(64 * 10, 0, 64, 64));
                else if (titleMap[i][j] == 'k')
                    map_sprite.setTextureRect(IntRect(64 * 11, 0, 64, 64));
                else if (titleMap[i][j] == 'l')
                    map_sprite.setTextureRect(IntRect(64 * 12, 0, 64, 64));
                else if (titleMap[i][j] == 'm')
                    map_sprite.setTextureRect(IntRect(64 * 13, 0, 64, 64));

                map_sprite.setPosition(j*64, i*64);
                window.draw(map_sprite);
            }
        return map_sprite;
    }

    Sprite DrawGrass(float time, RenderWindow &window)
    {
        int current_frame = 0;
        current_frame += (0.005*time);
        if(current_frame > 3)
                current_frame = 0;

        for(int i = 0; i < height_map_for_grass; ++i)
            for(int j = 0; j < width_map_for_grass; ++j)
            {
                if(grass_on_map[i][j] == ' ')
                {
                    grass_sprite.setTextureRect(IntRect(22 * int(current_frame), 0, 22, 17));
                }

                grass_sprite.setPosition(j*64, i*64);
                window.draw(grass_sprite);
            }
        return grass_sprite;

    }


};


int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ
    view.reset(FloatRect(0, 0, 1920, 1080));


    Map location("Map.end.PNG", "grass.PNG");
    Character Hero("hero.PNG", 200, 200, 96.0, 96.0, 0.1);


    while (window.isOpen())
    {
        float Time = clock.getElapsedTime().asMicroseconds();
        float time_environment = clock.getElapsedTime().asSeconds();

        clock.restart();
        Time /= 500;


        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            window.close();
        }

        Hero.Update(Time);

        window.setView(view);

        window.clear();

        location.DrawMap(window);
        location.DrawGrass(time_environment, window);

        Time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.draw(Hero.getSprite());
        window.display();

    }

    return 0;
}
