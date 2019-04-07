#include "pch.h"
#include <SFML/Graphics.hpp>
#include <locale>
#include "map.h"
#include "view.h"


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

	void Update(float time, Character Name)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = 3;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 288, 96, 96));

			getCharacterCoordinateView(Name.getCharacterCoordinateX(), Name.getCharacterCoordinateY());

		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = 2;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 0, 96, 96));

			getCharacterCoordinateView(Name.getCharacterCoordinateX(), Name.getCharacterCoordinateY());

		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = 1;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 96, 96, 96));

			getCharacterCoordinateView(Name.getCharacterCoordinateX(), Name.getCharacterCoordinateY());

		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = 0;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 192, 96, 96));

			getCharacterCoordinateView(Name.getCharacterCoordinateX(), Name.getCharacterCoordinateY());

		}

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

		x += ax * time;
		y += ay * time;

		speed = 0;

		sprite.setPosition(x, y);

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

};



class Map
{

private:

	Image map_image;
	Texture map_texture;
	Sprite map_sprite;

public:

	Map(String title_map)
	{
		map_image.loadFromFile("images/" + title_map);
		map_texture.loadFromImage(map_image);
		map_sprite.setTexture(map_texture);
	}

	void DrawMap(RenderWindow &window)
	{
		for (int i = 0; i < height_map; ++i)
			for (int j = 0; j < width_map; ++j)
			{
				if (titleMap[i][j] == ' ')
					map_sprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (titleMap[i][j] == 's')
					map_sprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (titleMap[i][j] == '0')
					map_sprite.setTextureRect(IntRect(64, 0, 32, 32));

				map_sprite.setPosition(j * 32, i * 32);
				window.draw(map_sprite);
			}
	}

};


int main()
{
	setlocale(LC_ALL, "RUS");

	Clock clock;

	RenderWindow window(VideoMode(1920, 1080), "");
	//window.setVerticalSyncEnabled(true); // Âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ
	view.reset(FloatRect(0, 0, 1920, 1080));

	Map location("map.PNG");
	Character Hero("hero.PNG", 860, 440, 96.0, 96.0, 0.1);


	while (window.isOpen())
	{
		float Time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Time /= 10;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}

		Hero.Update(Time, Hero);

		window.setView(view);

		window.clear();

		location.DrawMap(window);

		Time = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		window.draw(Hero.getSprite());
		window.display();

	}

	return 0;
}
