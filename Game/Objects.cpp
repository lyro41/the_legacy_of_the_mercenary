#include "pch.h"
#include "Objects.h"



Objects::Objects(std::string dir)
{
	grass_image.loadFromFile("images/grass.PNG");
	grass_texture.loadFromImage(grass_image);
	grass_sprite.setTexture(grass_texture);

	pearl_image.loadFromFile("images/pearl.PNG");
	pearl_texture.loadFromImage(pearl_image);
	pearl_sprite.setTexture(pearl_texture);

	this->LoadObjects(dir + "objects.TXT");
	this->ObjDef("locations/objects_define.TXT");
}



void Objects::LoadObjects(std::string dir)
{
	std::ifstream fin(dir);
	std::string buff;
	while (!fin.eof())
	{
		std::getline(fin, buff);
		objMap.push_back(buff);
	}
	height_objMap = objMap.size();
	width_objMap = objMap[0].length();
	fin.close();
}



void Objects::DrawObjects(float time, RenderWindow &window)
{

	current_frame += (0.005*time);
	if (current_frame > 4)
		current_frame = 0;

	for (int i = 0; i < height_objMap; ++i)
	{
		for (int j = 0; j < width_objMap; ++j)
		{
			if (objMap[i][j] == ' ')
			{
				grass_sprite.setTextureRect(IntRect(72 * int(current_frame), 0, 72, 64));
				grass_sprite.setPosition(j * 64, i * 64);
				window.draw(grass_sprite);
			}
			else if (objMap[i][j] == 'p')
			{
				pearl_sprite.setPosition(j * 64, i * 64);
				window.draw(pearl_sprite);
			}
		}
	}
}



void Objects::ObjDef(std::string dir)
{
	std::ifstream fin(dir);
	std::string buff;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > converter;
	while (!fin.eof())
	{
		getline(fin, buff);
		define.insert(std::make_pair(buff[0], converter.from_bytes(buff.substr(2, buff.length() - 2))));
	}
	fin.close();
}



String Objects::ObjectState(char tile)
{
	switch (tile)
	{
		case '0': return "static";
		case ' ': return "dynamic";
		case 'p': return "lootable";
		default: return "unknown";
	}
}