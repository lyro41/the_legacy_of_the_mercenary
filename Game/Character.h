#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Objects.h"
#include "Map.h"
#include "View.h"

using namespace sf;

class Character
{

private:
	float x, y, ws, hs, ax, ay, speed, original_speed;
	int dir = 0;
	Image image;
	Texture texture;
	Sprite sprite;
	float current_frame = 2;


public:
	Character(String title_pers, int X, int Y, float width_sprite, float height_sprite, float Speed);
	void Update(float time, Objects &objects_map, Camera &camera);
	float GetCharacterCoordinateX();
	float GetCharacterCoordinateY();
	Sprite GetSprite();
	void InteractionWithMap(String command, Objects &objects_map);
	
};

#endif // CHARACTER_H