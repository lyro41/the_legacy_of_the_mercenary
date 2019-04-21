#include "pch.h"
#include <SFML/Graphics.hpp>
#include "windows.h"
#include <locale>
#include "Character.h"
#include "Map.h"
#include "Objects.h"
#include "View.h"
#include "Geometry.h"
#include "Properties.h"


int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true);


    Map location("Map.end.blur.PNG", "grass.PNG");
    Character Hero("hero.PNG", 200, 200, 30, 60, 0.4);
	Objects objects;
	Camera camera(FloatRect(0, 0, 1920, 1080));
	Inventory inventory;
	PropertyList propertyList(L"Properties/");






    while (window.isOpen())
    {
        double Time = clock.getElapsedTime().asMicroseconds();
        double time_environment = clock.getElapsedTime().asSeconds();

        clock.restart();
        Time /= 500;


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) window.close();
			else if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::I) inventory.status = true;
        }


		if (inventory.status)
		{
			camera.camera_view.reset(FloatRect(0, 0, 1920, 1080));
			window.setView(camera.camera_view);
			while (window.isOpen() && inventory.status)
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed) window.close();
					else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == sf::Keyboard::I)) inventory.status = false;
				}
				inventory.Open(window, propertyList.properties);
			}
		}


        Hero.Update(Time, objects, camera, inventory, window);

        window.setView(camera.camera_view);

        window.clear();

        location.DrawMap(window);
        objects.DrawObjects(Time, window);

        Time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        window.draw(Hero.GetSprite());
        window.display();

    }

    return 0;
}
