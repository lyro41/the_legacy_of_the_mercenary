#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Map
{

private:
	Image map_image;
	Texture map_texture;
	Sprite map_sprite;


public:

	static const int height_map = 21;
	static const int width_map = 21;

	String tileMap[height_map] = {
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


	Map(String map_title, String title_grass);
	void DrawMap(RenderWindow &window);
	
};

#endif // MAP_H