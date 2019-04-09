#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View getCharacterCoordinateView(float x, float y)
{
    float tempX = x, tempY = y;

    if(x < 320)
        tempX = 320;
    if(x > 600)
        tempX = 600;
    if(y < 240)
        tempY = 240;
    if(y > 554)
        tempY = 554;

    view.setCenter(tempX, tempY);
    return view;
}
