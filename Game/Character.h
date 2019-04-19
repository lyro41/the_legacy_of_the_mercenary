#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Objects.h"
#include "Map.h"
#include "View.h"
#include "Inventory.h"

using namespace sf;

class Character
{

private:
	float prev_x = 0, prev_y = 0, x = 0, y = 0, ax = 0, ay = 0, speed = 0, original_speed = 0;
	int ws = 0, hs = 0, dir = 0;
	Image image;
	Texture texture;
	Sprite sprite;
	float current_frame = 2;


public:
	Character(String title_pers, int X, int Y, float width_sprite, float height_sprite, float Speed);
	void Update(float time, Objects &objects_map, Camera &camera, Inventory &inventory, RenderWindow &window);
	float GetCharacterCoordinateX();
	float GetCharacterCoordinateY();
	Sprite GetSprite();
	void InteractionWithMap(String command, RenderWindow &window, Objects &objects_map, Inventory inventory);
	
};

#endif // CHARACTER_H