#include "pch.h"
#include "Character.h"
#include "Geometry.h"
#include <iostream>

const int TILE_SIZE = 64;
const double MIN_TRAIL = 1e-8;
const double FRAME_SPEED = 20;

Character::Character(String title_pers, int X, int Y, double width_sprite, double height_sprite, double Speed)
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



void Character::Update(double time, Objects &objects, Camera &camera, Inventory &inventory, PropertyList &properties, RenderWindow &window, Map &map)
{
	Hitbox rect(0, 0, 1, 1, Pi / 4);
	prev_y = y;
	prev_x = x;
	speedAbs = original_speed;
	speedVector = Vector();

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		speedVector = speedVector - Vector(0, speedAbs);
		dir = 01;
	}

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		speedVector = speedVector + Vector(0, speedAbs);
		dir = 21;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		speedVector = speedVector + Vector(speedAbs, 0);
		dir = 12;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		speedVector = speedVector - Vector(speedAbs, 0);
		dir = 10;
	}

	speedVector.normalize(speedAbs);


	if (speedVector.abs() == 0)
	{
		current_frame = 1;
		switch (dir)
		{
		case 01:
			sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 128, 31, 60));
			break;
		case 10:
			sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 62, 31, 60));
			break;
		case 12:
			sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 193, 31, 60));
			break;
		default:
			sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 0, 31, 60));
		}

	}
	else
	{
		current_frame += (speedAbs / FRAME_SPEED * time);
		if (current_frame > 6)
		{
			if (speedVector.y != 0) current_frame = 1;
			if (speedVector.x != 0) current_frame = 2;
		}

		if (speedVector.y > 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 0, 31, 60));
		else if (speedVector.y < 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 128, 31, 60));

		if (speedVector.x > 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 193, 31, 60));
		else if (speedVector.x < 0) sprite.setTextureRect(IntRect(31 * static_cast<int>(current_frame), 62, 31, 60));
	}




	if (Keyboard::isKeyPressed(Keyboard::E))
	{
		this->InteractionWithMap("loot_check", window, objects, inventory, properties, map);
	}

	camera.GetCharacterCoordinateView(this->GetCharacterCoordinateX(), this->GetCharacterCoordinateY());

	x += speedVector.x * time;
	y += speedVector.y * time;

	speedAbs = 0;
	this->InteractionWithMap("static", window, objects, inventory, properties, map);

	sprite.setPosition(x, y);

}



double Character::GetCharacterCoordinateX()
{
	return x;
}



double Character::GetCharacterCoordinateY()
{
	return y;
}



Sprite Character::GetSprite()
{
	return sprite;
}



void Character::InteractionWithMap(String command, RenderWindow &window, Objects &objects, Inventory &inventory, PropertyList &properties, Map &map)
{
	if (command == "static")
	{
		for (double wy = y; wy <= y + hs; wy += hs)
		{
			for (double wx = x; wx <= x + ws; wx += ws)
			{
				int boxX = static_cast<int>(wx / TILE_SIZE);
				int boxY = static_cast<int>(wy / TILE_SIZE);
				if (map.tileMap[boxY][boxX] == '0')
				{
					Point choice(wx, wy);
					Line path(Point(prev_x + wx - x, prev_y + wy - y), Point(wx, wy));
					double distAB = path.vectorize().abs();
					double tx = boxX * TILE_SIZE, ty = boxY * TILE_SIZE;
					Point found[4] = {
						intersection(path, Line(Point(tx, ty), Point(tx + TILE_SIZE, ty))),
						intersection(path, Line(Point(tx, ty), Point(tx, ty + TILE_SIZE))),
						intersection(path, Line(Point(tx + TILE_SIZE, ty + TILE_SIZE), Point(tx, ty + TILE_SIZE))),
						intersection(path, Line(Point(tx + TILE_SIZE, ty + TILE_SIZE), Point(tx + TILE_SIZE, ty)))
					};
					for (int i = 0; i < 4; ++i)
					{
						if (dotProduct(Vector(found[i], path.p1), Vector(found[i], path.p2)) < 0)
						{
							bool U = map.tileMap[static_cast<int>((found[i].y - MIN_TRAIL) / TILE_SIZE)][static_cast<int>(found[i].x / TILE_SIZE)] != '0';
							bool D = map.tileMap[static_cast<int>((found[i].y + MIN_TRAIL) / TILE_SIZE)][static_cast<int>(found[i].x / TILE_SIZE)] != '0';
							bool L = map.tileMap[static_cast<int>(found[i].y / TILE_SIZE)][static_cast<int>((found[i].x - MIN_TRAIL) / TILE_SIZE)] != '0';
							bool R = map.tileMap[static_cast<int>(found[i].y / TILE_SIZE)][static_cast<int>((found[i].x + MIN_TRAIL) / TILE_SIZE)] != '0';
							if ((U ^ D || L ^ R) && Vector(path.p1, found[i]).abs() < distAB)
							{
								distAB = Vector(path.p1, found[i]).abs();
								choice = found[i];
							}
						}
					}
					double dx = choice.x - (speedVector.x ? speedVector.x / std::fabs(speedVector.x) : 0) * (choice.x == static_cast<int>(choice.x)) * 0.25 - wx;
					double dy = choice.y - (speedVector.y ? speedVector.y / std::fabs(speedVector.y) : 0) * (choice.y == static_cast<int>(choice.y)) * 0.25 - wy;
					if (map.tileMap[static_cast<int>((y + dy) / 64)][static_cast<int>((x + dx) / 64)] == '0'
						|| map.tileMap[static_cast<int>((y + dy + hs) / 64)][static_cast<int>((x + dx) / 64)] == '0'
						|| map.tileMap[static_cast<int>((y + dy) / 64)][static_cast<int>((x + dx + ws) / 64)] == '0'
						|| map.tileMap[static_cast<int>((y + dy + hs) / 64)][static_cast<int>((x + dx + ws) / 64)] == '0'
						) continue;
					x += dx;
					y += dy;
					return;
				}

			}
		}
	}
	else if (command == "loot_check")
	{

		int i = static_cast<int>(y + (hs / 2.0) * (1 + (speedVector.y > 0))) / 64;
		int j = static_cast<int>(x + ws * (speedVector.x > 0)) / 64;
		if (properties.objects[objects.define[objects.objMap[i][j]]]->interaction == "lootable")
		{
			inventory.AddToInventory(objects.define[objects.objMap[i][j]], properties.items);
			objects.objMap[i][j] = ' ';
		}
	}
}