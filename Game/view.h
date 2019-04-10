#pragma once
#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Camera
{

public:

	View camera_view;

	Camera(Rect<float> resolution);
	View GetCharacterCoordinateView(float x, float y);

};

#endif // VIEW_H