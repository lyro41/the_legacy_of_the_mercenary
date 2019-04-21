#include "pch.h"
#include "Map.h"

const int TILE_SIZE = 64;
const double MIN_TRAIL = 1e-8;



Map::Map(String map_title, String title_grass, std::string dir)
{
	map_image.loadFromFile("images/" + map_title);
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
	LoadMap(dir + "map.TXT");
}



void Map::LoadMap(std::string dir)
{
	std::ifstream fin(dir);
	std::string buff;
	while (!fin.eof())
	{
		std::getline(fin, buff);
		tileMap.push_back(buff);
	}
	height_map = tileMap.size();
	width_map = tileMap[0].length();
	fin.close();
}



void Map::DrawMap(RenderWindow &window)
{
	for (int i = 0; i < height_map; ++i)
		for (int j = 0; j < width_map; ++j)
		{
			if (tileMap[i][j] == ' ')
				map_sprite.setTextureRect(IntRect(0, 0, 64, 64));
			else if (tileMap[i][j] >= 'a' && tileMap[i][j] <= 'z')
				map_sprite.setTextureRect(IntRect(64 * (tileMap[i][j] - 'a' + 1), 0, 64, 64));
			else if (tileMap[i][j] == '0')
				map_sprite.setTextureRect(IntRect(0, 0, 64, 64));

			map_sprite.setPosition(j * 64, i * 64);
			window.draw(map_sprite);

		}
}