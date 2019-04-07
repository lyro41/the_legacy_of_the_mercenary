#include "pch.h"
#include <SFML/Graphics.hpp>
#include <locale>


using namespace sf;

class Character
{

private:


	float x, y, ws, hs, ax, ay, speed, original_speed;
	int dir = 0;
	String title;
	Image image;
	Texture texture;
	Sprite sprite;
	float current_frame = 0;


public:


	Character(String f, int X, int Y, float width_sprite, float height_sprite, float Speed)
	{
		title = f;
		ws = width_sprite;
		hs = height_sprite;
		image.loadFromFile("images/" + title);
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
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir = 3;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 288, 96, 96));

		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir = 2;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 0, 96, 96));

		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir = 1;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 96, 96, 96));

		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = 0;
			speed = original_speed;
			current_frame += (0.005*time);
			if (current_frame > 3)
				current_frame = 0;
			sprite.setTextureRect(IntRect(96 * int(current_frame), 192, 96, 96));

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

	Sprite getSprite()
	{
		return sprite;
	}

};

int main()
{
	setlocale(LC_ALL, "RUS");

	Clock clock;



	RenderWindow window(VideoMode(1920, 1080), "");
	//window.setVerticalSyncEnabled(true); // Âåðòèêàëüíàÿ ñèíõðîíèçàöèÿ

	Character Hero("hero.png", 100, 560, 96.0, 96.0, 0.1);


	while (window.isOpen())
	{
		float Time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		Time /= 500;


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				window.close();
		}

		Hero.Update(Time);


		window.clear();

		Time = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		window.draw(Hero.getSprite());
		window.display();

	}

	return 0;
}
