#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include "Geometry.h"

using namespace sf;



class Properties
{

public:
	Image image;
	Texture texture;
	Sprite sprite;
	std::string description;
	Point size;

	Properties(String dir, std::string description, Point size);

};



//std::unordered_map<std::string, Properties*> properties;



//void mapFiller();



class Inventory
{

private:

	const int width = 13, height = 8;
	const int LEFT_SPACE = 52, TOP_SPACE = 128;

	std::vector< std::vector<std::string> > inventory;
	Image inventory_box_image;
	Texture inventory_box_texture;
	Sprite inventory_box;
	Sprite inventory_box_filler_top;
	Sprite inventory_box_filler_bottom;


public:
	bool status = false;

	Inventory();
	void Close(RenderWindow &window);
	void Open(RenderWindow &window);
	void AddToInventory(char obj, RenderWindow &window);

};

#endif // INVENTORY_H