#include "pch.h"
#include "View.h"



Camera::Camera(Rect<float> resolution)
{
	camera_view.reset(resolution);
}



View Camera::GetCharacterCoordinateView(float x, float y)
{
	float tempX = x, tempY = y;

	if (x < 1024)
		tempX = 1024;
	if (x > 2312)
		tempX = 2312;
	if (y < 604)
		tempY = 604;
	if (y > 804)
		tempY = 804;

	camera_view.setCenter(tempX, tempY);
	return camera_view;
}