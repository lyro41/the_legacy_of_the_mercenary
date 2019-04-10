#pragma once
#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Objects
{

private:

	Image grass_image;
	Texture grass_texture;
	Sprite grass_sprite;

	float current_frame = 0;


public:

	static const int height_map_for_objects = 21;
	static const int width_map_for_objects = 21;

	sf::String objects_map[height_map_for_objects] = {
		"000000000000000000000",
		"0                   0",
		"0                   0",
		"0                   0",
		"0                   0",
		"0         abbbbbbbbb0",
		"0        akeeeeeeeee0",
		"0       akeeeeeeeeee0",
		"0      akeelhhhhhhhh0",
		"0     akeeli        0",
		"0     deeli         0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"0     deef          0",
		"000000000000000000000"
	};

	Objects();
	void DrawObjects(float time, RenderWindow &window);
	String ObjectState(char tile);
	void MovingTo(String state);

};

#endif // OBJECTS_H