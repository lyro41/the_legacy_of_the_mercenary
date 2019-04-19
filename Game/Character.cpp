#include "pch.h"
#include "Character.h"



Character::Character(String title_pers, int X, int Y, float width_sprite, float height_sprite, float Speed)
{
	ws = width_sprite;
	hs = height_sprite;
	image.loadFromFile("images/" + title_pers);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X;
	y = Y;
	sprite.setTextureRect(IntRect(ws, hs, ws, hs));
	original_speed = Speed;
	sprite.setPosition(x, y);
}



void Character::Update(float time, Objects &objects, Camera &camera, Inventory &inventory, RenderWindow &window)
{
	speed = original_speed;
	ax = 0;
	ay = 0;

	if (Keyboard::isKeyPressed(Keyboard::W)) ay -= speed;

	if (Keyboard::isKeyPressed(Keyboard::S)) ay += speed;

	if (Keyboard::isKeyPressed(Keyboard::A)) ax -= speed;

	if (Keyboard::isKeyPressed(Keyboard::D)) ax += speed;

	if (ax == 0 && ay == 0)
	{
		//current_frame = 1;

		// some code
	}
	else
	{
		current_frame += (speed / 20 * time);
		if (current_frame > 6)
		{
			if (ay != 0) current_frame = 1;
			if (ax != 0) current_frame = 2;
		}
		
		if (ay > 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 0, 31, 60));
		else if (ay < 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 128, 31, 60));

		if (ax > 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 193, 31, 60));
		else if (ax < 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 62, 31, 60));
	}

	


	if (Keyboard::isKeyPressed(Keyboard::I))
	{
		if (inventory.GetStatus()) inventory.Close(window);
		else inventory.Open(window);
	}
	else if (Keyboard::isKeyPressed(Keyboard::E))
	{
		this->InteractionWithMap("loot_check", window, objects, inventory);
	}

	camera.GetCharacterCoordinateView(this->GetCharacterCoordinateX(), this->GetCharacterCoordinateY());

	x += ax * time;
	y += ay * time;

	speed = 0;

	sprite.setPosition(x, y);
	this->InteractionWithMap("static", window, objects, inventory);

}



float Character::GetCharacterCoordinateX()
{
	return x;
}



float Character::GetCharacterCoordinateY()
{
	return y;
}



Sprite Character::GetSprite()
{
	return sprite;
}



void Character::InteractionWithMap(String command, RenderWindow &window, Objects &objects, Inventory inventory)
{
	if (command == "static")
	{
		for (int i = y / 64; i < (y + hs) / 64; ++i)
		{
			for (int j = x / 64; j < (x + ws) / 64; ++j)
			{
				if (objects.objects_map[i][j] == '0')
				{
					if (ax == 0) y = i * 64 + 64 * (ay < 0) - hs * (ay > 0);
					else x = j * 64 + 64 * (ax < 0) - ws * (ax > 0);
				}
			}
		}
	}
	else if (command == "loot_check")
	{

		int Y = static_cast<int> (y);
		int X = static_cast<int> (x);

		if (ay > 0)
		{
			
			if (objects.ObjectState(objects.objects_map[Y / 64 + 1][X / 64]) == "lootable")
			{
				inventory.AddToInventory(objects.objects_map[Y / 64 + 1][X / 64], window);
				objects.objects_map[Y / 64 + 1][X / 64] = ' ';
			}
			
		}
		else if (ay < 0)
		{
			if (objects.ObjectState(objects.objects_map[Y / 64][X / 64]) == "lootable")
			{
				inventory.AddToInventory(objects.objects_map[Y / 64][X / 64], window);
				objects.objects_map[Y / 64][X / 64] = ' ';
			}
		}
		else if (ax > 0)
		{
			if (objects.ObjectState(objects.objects_map[Y / 64 + 1][X / 64 + 1]) == "lootable")
			{
				inventory.AddToInventory(objects.objects_map[Y / 64 + 1][X / 64 + 1], window);
				objects.objects_map[Y / 64 + 1][X / 64 + 1] = ' ';
			}
		}
		else if (ax < 0)
		{
			if (objects.ObjectState(objects.objects_map[Y / 64 + 1][X / 64 - 1]) == "lootable")
			{
				inventory.AddToInventory(objects.objects_map[Y / 64 + 1][X / 64 - 1], window);
				objects.objects_map[Y / 64 + 1][X / 64 - 1] = ' ';
			}
		}
	}
}