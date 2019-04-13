#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Inventory
{

private:
	char inventory[8][16];
	Image inventory_image;
	Texture inventory_texture;
	Sprite inventory_sprite;
	bool status = false;


public:
	Inventory();
	bool GetStatus();
	void Close(RenderWindow &window);
	void Open(RenderWindow &window);
	void AddToInventory(char obj, RenderWindow &window);

};

#endif // INVENTORY_H