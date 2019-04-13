#include "pch.h"
#include "Inventory.h"



Inventory::Inventory()
{
	inventory_image.loadFromFile("inventory.PNG");
	inventory_texture.loadFromImage(inventory_image);
	inventory_sprite.setTexture(inventory_texture);

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			inventory[i][j] = '0';
		}
	}
}



bool Inventory::GetStatus()
{
	return status;
}



void Inventory::Close(RenderWindow &window)
{
	status = false;
}



void Inventory::Open(RenderWindow &window)
{
	window.draw(inventory_sprite);
	/*
		show items
	*/
	status = true;
}



void Inventory::AddToInventory(char obj, RenderWindow &window)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (inventory[i][j] == '0')
			{
				inventory[i][j] = obj;
				goto ex;
			}
		}
	}
	ex: this->Open(window);
}