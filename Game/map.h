#pragma once
#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <codecvt>

using namespace sf;

class Map
{

private:
	Image map_image;
	Texture map_texture;
	Sprite map_sprite;


public:

	int height_map;
	int width_map;
	
	std::vector<std::string> tileMap;
	std::map<char, std::wstring> define;


	Map(String map_title, String title_grass, std::string dir);
	void LoadMap(std::string dir);
	void MapDef(std::string dir);
	void DrawMap(RenderWindow &window);
	
};

#endif // MAP_H