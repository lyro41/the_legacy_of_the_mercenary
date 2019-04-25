#include "pch.h"
#include "Inventory.h"



Inventory::Inventory()
{
	background_image.loadFromFile("images/inventory/background.PNG");
	background_texture.loadFromImage(background_image);
	background.setTexture(background_texture);
	background.setTextureRect(IntRect(0, 0, 1920, 1080));

	slots_image.loadFromFile("images/inventory/slots.PNG");
	slots_texture.loadFromImage(slots_image);

	slot_1x1.setTexture(slots_texture);
	slot_1x1.setTextureRect(IntRect(68, 0, 72, 72));

	slot_1x2.setTexture(slots_texture);
	slot_1x2.setTextureRect(IntRect(0, 0, 72, 140));
	

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
	window.draw(background);
	for (int j = 0; j < width; ++j)
	{
		for (int i = 0; i < height; ++i)
		{
			if (items[inventory[i][j]]->size != Point(1, 1))
			{
				slot_1x2.setPosition(LEFT_SPACE + j * 68, TOP_SPACE + i * 68);
				window.draw(slot_1x2);
			}
			else if (inventory[i][j] != L"SEE_TOP")
			{
				slot_1x1.setPosition(LEFT_SPACE + j * 68, TOP_SPACE + i * 68);
				window.draw(slot_1x1);
			}

			if (inventory[i][j] != L"EMPTY")
			{
				items[inventory[i][j]]->sprite.setPosition(LEFT_SPACE + 4 + j * 68, TOP_SPACE + 4 + i * 68);
				window.draw(items[inventory[i][j]]->sprite);
			}
		}
	}
	window.display();
}



void Inventory::AddToInventory(std::wstring obj, std::unordered_map<std::wstring, Properties*> &items, RenderWindow &window)
{
	if (items[obj]->size == Point(1, 1))
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (inventory[i][j] == L"EMPTY")
				{
					inventory[i][j] = obj;
					return;
				}
			}
		}
	}
	else if (items[obj]->size == Point(1, 2))
	{
		for (int i = 0; i < height - 1; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (inventory[i][j] == L"EMPTY" && inventory[i][j] == L"EMPTY")
				{
					inventory[i][j] = obj;
					return;
				}
			}
		}
	}
}



void Inventory::main(RenderWindow &window, Camera &camera, PropertyList &properties)
{

	camera.camera_view.reset(FloatRect(0, 0, 1920, 1080));
	window.setView(camera.camera_view);
	Event event;
	/*int i, j, dx, dy;*/
	while (window.isOpen() && status)
	{

		/*Vector2i pos = Mouse::getPosition(window);
		pos.x -= LEFT_SPACE;
		pos.y -= TOP_SPACE;
		i = pos.y / 64;
		j = pos.x / 64;*/

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == sf::Keyboard::I))
			{
				status = false;
				return;
			}

			/*if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && inventory[i][j] != L"EMPTY")
			{
				dx = pos.x - properties.items[inventory[i][j]]->sprite.getPosition().x;
				dy = pos.y - properties.items[inventory[i][j]]->sprite.getPosition().y;
				isDrag = true;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left) isDrag = false;*/

		}

		/*if (isDrag)
		{
			
		}*/

		this->Open(window, properties.items);

	}
}