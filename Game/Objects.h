#pragma once
#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <codecvt>
#include <map>
#include <iostream>

using namespace sf;

class Objects
{

private:

	Image grass_image;
	Texture grass_texture;
	Sprite grass_sprite;

	Image pearl_image;
	Texture pearl_texture;
	Sprite pearl_sprite;

	Image fir_image;
	Texture fir_texture;
	Sprite fir_sprite;

	Image big_fir_image;
	Texture big_fir_texture;
	Sprite big_fir_sprite;

	float current_frame = 0;


public:

	int height_objMap;
	int width_objMap;

	std::vector<std::string> objMap;
	std::map<char, std::wstring> define;

	Objects(std::string dir);
	void LoadObjects(std::string dir);
	void DrawObjects(float time, RenderWindow &window);
	void ObjDef(std::string dir);
	String ObjectState(char tile);

};

#endif // OBJECTS_H