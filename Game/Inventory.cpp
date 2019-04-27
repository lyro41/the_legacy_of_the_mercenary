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



Point Inventory::EmptySearch(std::wstring obj, std::unordered_map<std::wstring, Properties*> &items)
{
	if (items[obj]->size == Point(1, 1))
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				if (inventory[i][j] == L"EMPTY")
				{
					return Point(j, i);
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
				if (inventory[i][j] == L"EMPTY" && inventory[i + 1][j] == L"EMPTY")
				{
					return Point(j, i);
				}
			}
		}
	}
}



void Inventory::Open(RenderWindow &window, std::unordered_map<std::wstring, Properties*> &items)
{
	window.clear();
	window.draw(background);
	Font font;
	font.loadFromFile("fonts/CyrilicOld.TTF");
	Text counter("", font, 20);
	counter.setStyle(Text::Bold);
	for (int j = 0; j < width; ++j)
	{
		for (int i = 0; i < height; ++i)
		{
			if (items[inventory[i][j]]->size == Point(1, 2))
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

				if (items[inventory[i][j]]->quantity > 1)
				{
					counter.setString(std::to_string(items[inventory[i][j]]->quantity));
					counter.setOrigin(counter.getLocalBounds().width, counter.getLocalBounds().height);
					counter.setPosition(LEFT_SPACE + 66 + j * 68, TOP_SPACE + 60 + i * 68);
					window.draw(counter);
				}
			}
		}
	}

	if (isDrag)
	{
		Dragged.setPosition(x, y);
		window.draw(Dragged);
	}

	window.display();
}



void Inventory::AddToInventory(std::wstring obj, std::unordered_map<std::wstring, Properties*> &items)
{
	if (items[obj]->quantity) items[obj]->quantity += 1;
	else
	{
		Point empty = this->EmptySearch(obj, items);
		inventory[empty.y][empty.x] = obj;
		if (items[obj]->size == Point(1, 2)) inventory[empty.y + 1][empty.x] == L"SEE_TOP";
		items[obj]->quantity = 1;
	}
}



void Inventory::main(RenderWindow &window, Camera &camera, PropertyList &properties)
{

	camera.camera_view.reset(FloatRect(0, 0, 1920, 1080));
	window.setView(camera.camera_view);
	Event event;
	int i = -1, j = -1, dx, dy;
	std::cout << properties.items[L"pearl"]->quantity << '\n';

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	while (window.isOpen() && status)
	{

		Vector2i pos = Mouse::getPosition(window);
		pos.x -= LEFT_SPACE;
		pos.y -= TOP_SPACE;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Escape || event.key.code == sf::Keyboard::I))
			{
				status = false;
				isDrag = false;
				if (i >= 0 && j >= 0) properties.items[inventory[i][j]]->sprite.setColor(Color::White);
				i = -1;
				j = -1;
				return;
			}

			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && (pos.y >= 0 && pos.x >= 0 && pos.x / 68 < width && pos.y / 68 < height) && inventory[pos.y / 68][pos.x / 68] != L"EMPTY")
			{
				i = pos.y / 68;
				j = pos.x / 68;
				if (inventory[i][j] == L"SEE_TOP") --i;
				Dragged = properties.items[inventory[i][j]]->sprite;
				dx = pos.x - properties.items[inventory[i][j]]->sprite.getPosition().x;
				dy = pos.y - properties.items[inventory[i][j]]->sprite.getPosition().y;
				Color color = Color::White;
				color.a = 75;
				properties.items[inventory[i][j]]->sprite.setColor(color);
				isDrag = true;
			}

			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && i >= 0 && j >= 0)
			{
				isDrag = false;
				properties.items[inventory[i][j]]->sprite.setColor(Color::White);

				IntRect drag_rect = Dragged.getTextureRect();
				int to_i = (pos.y - dy - drag_rect.height / 2) / 68;
				int to_j = (pos.x - dx - drag_rect.width / 2) / 68;
				if (i >= 0 && j >= 0 && to_i < height && to_j < width && to_i >= 0 && to_j >= 0)
				{

					if (properties.items[inventory[i][j]]->size == Point(1, 1) && inventory[to_i][to_j] == L"EMPTY")
					{
						inventory[to_i][to_j] = inventory[i][j];
						inventory[i][j] = L"EMPTY";
					}
					else if (properties.items[inventory[i][j]]->size == Point(1, 2) && (inventory[to_i][to_j] == L"EMPTY" || (to_i == i + 1 && to_j == j)) && to_i < height - 1 && (inventory[to_i + 1][to_j] == L"EMPTY" || (to_i == i - 1 && to_j == j)))
					{
						std::wstring temp = inventory[i][j];
						inventory[i][j] = L"EMPTY";
						inventory[i + 1][j] = L"EMPTY";
						inventory[to_i][to_j] = temp;
						inventory[to_i + 1][to_j] = L"SEE_TOP";
					}

				}
				i = -1;
				j = -1;
			}

		}

		if (isDrag)
		{
			x = pos.x - dx;
			y = pos.y - dy;
		}

		this->Open(window, properties.items);

	}
}