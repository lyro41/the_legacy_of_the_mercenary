#include "pch.h"
#include "Inventory.h"



Inventory::Inventory()
{
	inventory_box_image.loadFromFile("images/inventory_box.PNG");
	inventory_box_texture.loadFromImage(inventory_box_image);

	inventory_box.setTexture(inventory_box_texture);
	inventory_box.setTextureRect(IntRect(1, 1, 64, 64));

	inventory_box_filler_top.setTexture(inventory_box_texture);
	inventory_box_filler_top.setTextureRect(IntRect(1, 4, 64, 5));

	inventory_box_filler_bottom.setTexture(inventory_box_texture);
	inventory_box_filler_bottom.setTextureRect(IntRect(1, 4, 64, 61));

	inventory.resize(height);

	for (int i = 0; i < height; ++i)
	{
		inventory[i] = std::vector<std::wstring>(width, L"EMPTY");
	}

}



void Inventory::Close(RenderWindow &window)
{
	status = false;
}



void Inventory::Open(RenderWindow &window, std::unordered_map<std::wstring, Properties*> &properties)
{
	window.clear();
	for (int j = 0; j < width; ++j)
	{
		for (int i = 0; i < height; ++i)
		{
			if (properties[inventory[i][j]]->size != Point(1, 1))
			{
				inventory_box.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
				window.draw(inventory_box);
				inventory_box_filler_top.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66 + 64);
				inventory_box_filler_bottom.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66 + 69);
				window.draw(inventory_box_filler_top);
				window.draw(inventory_box_filler_bottom);
			}
			else if (inventory[i][j] != L"SEE_TOP")
			{
				inventory_box.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
				window.draw(inventory_box);
			}
		}
	}
	/*
		show items
	*/
	window.display();
}



void Inventory::AddToInventory(char obj, RenderWindow &window)
{
	/*for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (inventory[i][j] == "")
			{
				inventory[i][j] = obj;
				return;
			}
		}
	}*/
}