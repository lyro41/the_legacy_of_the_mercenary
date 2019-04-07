#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View getCharacterCoordinateView(float x, float y)
{
    view.setCenter(x+100, y+100);
    return view;
}
