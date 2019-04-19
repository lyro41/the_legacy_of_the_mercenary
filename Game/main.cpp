#include "pch.h"
#include <SFML/Graphics.hpp>
#include <locale>
#include "Character.h"
#include "Map.h"
#include "Objects.h"
#include "View.h"



int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    //window.setVerticalSyncEnabled(true); // Âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ


    Map location("Map.end.blur.PNG", "grass.PNG");
    Character Hero("hero.PNG", 200, 200, 30, 60, 0.1);
	Objects objects;
	Camera camera(FloatRect(0, 0, 1920, 1080));
	Inventory inventory;






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
