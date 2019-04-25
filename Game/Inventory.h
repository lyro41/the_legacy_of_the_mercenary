#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
#include "Geometry.h"
#include "Properties.h"
#include "View.h"

using namespace sf;



class Inventory
{

private:

	const int width = 13, height = 8;
	const int LEFT_SPACE = 52, TOP_SPACE = 128;

	bool isDrag = false;

	std::vector< std::vector<std::wstring> > inventory;

	Image background_image;
	Image slots_image;
	Image info_image;
	Image buttons_image;

	Texture background_texture;
	Texture slots_texture;
	Texture info_texture;
	Texture buttons_texture;

	Sprite background;
	Sprite slot_1x1;
	Sprite slot_1x2;
	Sprite info;

	std::vector<Sprite> quest_button;
	std::vector<Sprite> inventory_button;


public:
	bool status = false;

	Inventory();
	void Close(RenderWindow &window);
	void Open(RenderWindow &window, std::unordered_map<std::wstring, Properties*> &items);
	void AddToInventory(std::wstring obj, std::unordered_map<std::wstring, Properties*> &items, RenderWindow &window);
	void main(RenderWindow &window, Camera &camera, PropertyList &properties);

};

#endif // INVENTORY_H