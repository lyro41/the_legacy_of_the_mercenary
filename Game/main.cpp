#include "pch.h"
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
    float current_frame = 2;


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

    void Update(Map &objects, float time)
    {
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            dir = 3;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 6)
                current_frame = 2;
            sprite.setTextureRect(IntRect(31* int(current_frame), 128 , 31, 60));

        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            dir = 2;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 6)
                current_frame = 2;
            sprite.setTextureRect(IntRect(31* int(current_frame), 0 , 31, 60));

        }
        else if (Keyboard::isKeyPressed(Keyboard::A))
        {
            dir = 1;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 6)
                current_frame = 1;
            sprite.setTextureRect(IntRect(31* int(current_frame), 62 , 31, 60));

        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            dir = 0;
            speed = original_speed;
            current_frame += (0.005*time);
            if(current_frame > 6)
                current_frame = 1;
            sprite.setTextureRect(IntRect(31* int(current_frame), 193 , 31, 60));

        }

		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			this->interactionWithMap("loot_check");
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
        this->interactionWithMap();

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
        for (int i = y / 64; i < (y + hs) / 64; ++i)
            for (int j = x / 64; j < (x + ws) / 64; ++j)
            {
                if (objects_map[i][j] == '0')
                {

                    if (ay > 0)
                    {
                        y = i * 64 - hs;
                    }
                    else if (ay < 0)
                    {
                        y = i * 64 + 64;
                    }
                    else if (ax > 0)
                    {
                        x = j * 64 - ws;
                    }
                    else if (ax < 0)
                    {
                        x = j * 64 + 64;
                    }

                }
            }

    }

	void interactionWithMap(String command)
	{
		if (command == "loot_check")
		{
			if (ay > 0)
			{
				/*
				if (Objects.lootable_objects(objects_map[y / 64 + 1][x / 64])
				{
					Inventory.addToInventory(objects_map[y / 64 + 1][x / 64]);
					objects_map[y / 64 + 1][x / 64] = '\0';
				}
				*/
			}
			else if (ay < 0)
			{
				/*
				if (Objects.lootable_objects(objects_map[y / 64 - 1][x / 64])
				{
					Inventory.addToInventory(objects_map[y / 64 - 1][x / 64]);
					objects_map[y / 64 - 1][x / 64] = '\0';
				}
				*/
			}
			else if (ax > 0)
			{
				/*
				if (Objects.lootable_objects(objects_map[y / 64][x / 64 + 1])
				{
					Inventory.addToInventory(objects_map[y / 64][x / 64 + 1]);
					objects_map[y / 64][x / 64 + 1] = '\0';
				}
				*/
			}
			else if (ax < 0)
			{
				/*
				if (Objects.lootable_objects(objects_map[y / 64][x / 64 - 1])
				{
					Inventory.addToInventory(objects_map[y / 64][x / 64 - 1]);
					objects_map[y / 64][x / 64 - 1] = '\0';
				}
				*/
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

    float current_frame = 0;

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

    void DrawMap(RenderWindow &window)
    {
        for (int i = 0; i < height_map; ++i)
            for (int j = 0; j < width_map; ++j)
            {
                if (titleMap[i][j] == ' ')
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
    }

    void DrawObjects(float time, RenderWindow &window)
    {

        current_frame += (0.005*time);
        if(current_frame > 4)
                current_frame = 0;

        for(int i = 0; i < height_map_for_objects; ++i)
            for(int j = 0; j < width_map_for_objects; ++j)
            {
                if(objects_map[i][j] == ' ')
                {
                    grass_sprite.setTextureRect(IntRect(72 * int(current_frame), 0, 72, 64));
                    grass_sprite.setPosition(j*64, i*64);
                    window.draw(grass_sprite);
                }
            }
    }

	bool lootable_objects(char name)
	{
		switch (name)
		{
			case '0': return false;
			case ' ': return false;
		}
	}

};

/*
class Inventory
{
private:

    char inventory[8][16];
    Image inventory_image;
    Texture inventory_texture;
    Sprite inventory_sprite;

public:

    Inventory()
    {
        inventory_image.loadFromFile("inventory.PNG");
        inventory_texture.loadFromImage(inventory_image);
        inventory_sprite.setTexture(inventory_texture);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 16; ++j)
            {
                inventory[i][j] = '0';
            }
    }

    void openInventory (RenderWindow &window)
    {
        if (Keyboard::isKeyPressed(Keyboard::I))
        {
            window.draw(inventory_sprite);
        }

    }

    void putInside (char obj, RenderWindow &window)
    {
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 16; ++j)
            {
                if (inventory[i][j] == '0')
                    inventory[i][j] = obj;
                window.draw(inventory_sprite);
            }

    }


};
*/

int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ
    view.reset(FloatRect(0, 0, 1920, 1080));


    Map location("Map.end.blur.PNG", "grass.PNG");
    Character Hero("hero.PNG", 200, 200, 30, 60, 0.1);






    while (window.isOpen())
    {
        float Time = clock.getElapsedTime().asMicroseconds();
        float time_environment = clock.getElapsedTime().asSeconds();

        clock.restart();
        Time /= 500;


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            window.close();
        }

        Hero.Update(Time);

        window.setView(view);

        window.clear();

        location.DrawMap(window);
        location.DrawObjects(Time, window);

        Time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.draw(Hero.getSprite());
        window.display();

    }

    return 0;
}
