#include "pch.h"
#include "View.h"

Camera::Camera(Rect<float> resolution)
{
	camera_view.reset(resolution);
}



View Camera::GetCharacterCoordinateView(float x, float y)
{
	float tempX = x, tempY = y;

	if (x < 320)
		tempX = 320;
	if (x > 600)
		tempX = 600;
	if (y < 240)
		tempY = 240;
	if (y > 554)
		tempY = 554;

	camera_view.setCenter(tempX, tempY);
	return camera_view;
}