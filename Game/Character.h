#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <codecvt>
#include "Objects.h"
#include "Map.h"
#include "View.h"
#include "Inventory.h"
#include "Geometry.h"
#include "Properties.h"

using namespace sf;

class Character
{

private:
	double prev_x = 0, prev_y = 0, x = 0, y = 0, speedAbs = 0, original_speed = 0;
	Vector speedVector;
	int ws = 0, hs = 0, dir = 0;
	Image image;
	Texture texture;
	Sprite sprite;
	double current_frame = 2;


public:
	Character(String title_pers, int X, int Y, double width_sprite, double height_sprite, double Speed);
	void Update(double time, Objects &objects_map, Camera &camera, Inventory &inventory, PropertyList &properties, RenderWindow &window);
	double GetCharacterCoordinateX();
	double GetCharacterCoordinateY();
	Sprite GetSprite();
	void InteractionWithMap(String command, RenderWindow &window, Objects &objects_map, Inventory &inventory, PropertyList &properties);

};

#endif // CHARACTER_H