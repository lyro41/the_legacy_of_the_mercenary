#pragma once
#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <fstream>
#include <Windows.h>
#include <codecvt>
#include <iostream>
#include <vector>
#include "Geometry.h"

using namespace sf;



class Properties
{

public:
	Image image;
	Texture texture;
	Sprite sprite;
	std::string description;
	Point size;
	std::string update, interaction;

	std::vector<Sprite> status;

	Properties(std::string dir, std::string description, Point size);
	Properties(std::string dir, int frames, std::string interaction, Point size);

};



class PropertyList
{
	
public:
	std::unordered_map<std::wstring, Properties*> items;
	std::unordered_map<std::wstring, Properties*> objects;

	PropertyList(std::wstring dir);
	void ItemFiller(std::wstring directory);
	void ObjectFiller(std::wstring directory);
};





#endif // PROPERTIES_H