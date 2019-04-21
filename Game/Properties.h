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

	Properties(std::string dir, std::string description, Point size);

};



class PropertyList
{
	
public:
	std::unordered_map<std::wstring, Properties*> properties;

	PropertyList(std::wstring dir);
	void Filler(std::wstring dir);
};





#endif // PROPERTIES_H