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

	inventory[0][0] = L"familiar_sword";
	inventory[1][0] = L"SEE_TOP";

}



void Inventory::Close(RenderWindow &window)
{
	status = false;
}



void Inventory::Open(RenderWindow &window, std::unordered_map<std::wstring, Properties*> &items)
{
	window.clear();
	for (int j = 0; j < width; ++j)
	{
		for (int i = 0; i < height; ++i)
		{
			if (items[inventory[i][j]]->size != Point(1, 1))
			{
				inventory_box.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
				window.draw(inventory_box);
				inventory_box_filler_top.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66 + 64);
				inventory_box_filler_bottom.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66 + 69);
				window.draw(inventory_box_filler_top);
				window.draw(inventory_box_filler_bottom);

				if (inventory[i][j] != L"EMPTY")
				{
					items[inventory[i][j]]->sprite.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
					window.draw(items[inventory[i][j]]->sprite);
				}
			}
			else if (inventory[i][j] != L"SEE_TOP")
			{
				inventory_box.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
				window.draw(inventory_box);
				if (inventory[i][j] != L"EMPTY")
				{
					items[inventory[i][j]]->sprite.setPosition(LEFT_SPACE + j * 66, TOP_SPACE + i * 66);
					window.draw(items[inventory[i][j]]->sprite);
				}
			}
		}
	}
	window.display();
}



void Inventory::AddToInventory(std::wstring obj, std::unordered_map<std::wstring, Properties*> &items, RenderWindow &window)
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
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{

		}
	}
}