#include "pch.h"
#include "Map.h"



Map::Map(String map_title, String title_grass)
{
	map_image.loadFromFile("images/" + map_title);
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
}



void Map::DrawMap(RenderWindow &window)
{
	for (int i = 0; i < height_map; ++i)
		for (int j = 0; j < width_map; ++j)
		{
			if (tileMap[i][j] == ' ')
				map_sprite.setTextureRect(IntRect(0, 0, 64, 64));
			else if (tileMap[i][j] == 'a')
				map_sprite.setTextureRect(IntRect(64, 0, 64, 64));
			else if (tileMap[i][j] == 'b')
				map_sprite.setTextureRect(IntRect(64 * 2, 0, 64, 64));
			else if (tileMap[i][j] == 'c')
				map_sprite.setTextureRect(IntRect(64 * 3, 0, 64, 64));
			else if (tileMap[i][j] == 'd')
				map_sprite.setTextureRect(IntRect(64 * 4, 0, 64, 64));
			else if (tileMap[i][j] == 'e')
				map_sprite.setTextureRect(IntRect(64 * 5, 0, 64, 64));
			else if (tileMap[i][j] == 'f')
				map_sprite.setTextureRect(IntRect(64 * 6, 0, 64, 64));
			else if (tileMap[i][j] == 'g')
				map_sprite.setTextureRect(IntRect(64 * 7, 0, 64, 64));
			else if (tileMap[i][j] == 'h')
				map_sprite.setTextureRect(IntRect(64 * 8, 0, 64, 64));
			else if (tileMap[i][j] == 'i')
				map_sprite.setTextureRect(IntRect(64 * 9, 0, 64, 64));
			else if (tileMap[i][j] == 'j')
				map_sprite.setTextureRect(IntRect(64 * 10, 0, 64, 64));
			else if (tileMap[i][j] == 'k')
				map_sprite.setTextureRect(IntRect(64 * 11, 0, 64, 64));
			else if (tileMap[i][j] == 'l')
				map_sprite.setTextureRect(IntRect(64 * 12, 0, 64, 64));
			else if (tileMap[i][j] == 'm')
				map_sprite.setTextureRect(IntRect(64 * 13, 0, 64, 64));
			else if (tileMap[i][j] == '0')
				map_sprite.setTextureRect(IntRect(0, 0, 64, 64));

			map_sprite.setPosition(j * 64, i * 64);
			window.draw(map_sprite);

		}
}