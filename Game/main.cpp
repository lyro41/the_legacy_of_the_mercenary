#include "pch.h"
#include <SFML/Graphics.hpp>
#include <locale>
#include "Character.h"
#include "Map.h"
#include "Objects.h"
#include "View.h"

extern View camera_view;

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


    Map location("Map.end.blur.PNG", "grass.PNG");
    Character Hero("hero.PNG", 200, 200, 30, 60, 0.1);
	Objects objects_map;
	Camera camera(FloatRect(0, 0, 1920, 1080));






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

        Hero.Update(Time, objects_map, camera);

        window.setView(camera.camera_view);

        window.clear();

        location.DrawMap(window);
        objects_map.DrawObjects(Time, window);

        Time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.draw(Hero.GetSprite());
        window.display();

    }

    return 0;
}
