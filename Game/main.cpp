#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "windows.h"
#include <locale>
#include "Character.h"
#include "Map.h"
#include "Objects.h"
#include "View.h"
#include "Geometry.h"
#include "Properties.h"

const int TRACKS_QUAN = 2;


int main()
{
    setlocale(LC_ALL,"RUS");

    Clock clock;



    RenderWindow window(VideoMode(1920, 1080), "");
    window.setVerticalSyncEnabled(true);


    Map location("Map.end.blur.PNG", "grass.PNG", "locations/main/");
    Character Hero("hero.PNG", 200, 200, 30, 60, 0.4);
	Objects objects("locations/main/");
	Camera camera(FloatRect(0, 0, 1920, 1080));
	Inventory inventory;
	PropertyList properties(L"properties/");


	
	Music main_theme;
	int track = 1;
	main_theme.openFromFile("music/main_theme_1.ogg");
	main_theme.play();
	main_theme.setVolume(10);


    while (window.isOpen())
    {
        double Time = clock.getElapsedTime().asMicroseconds();
        double time_environment = clock.getElapsedTime().asSeconds();

        clock.restart();
        Time /= 1500;

		if (main_theme.getStatus() == SoundSource::Stopped)
		{
			if (++track > TRACKS_QUAN) track = 1;
			main_theme.openFromFile("music/main_theme_" + std::to_string(track) + ".ogg");
			main_theme.play();
		}

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) window.close();
			else if (event.type == Event::KeyPressed && event.key.code == sf::Keyboard::I) inventory.status = true;
        }

		
		inventory.main(window, camera, properties, main_theme);


        Hero.Update(Time, objects, camera, inventory, properties, window);

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
