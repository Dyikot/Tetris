#include "Control.h"

void Control::SetWidth(int width)
{
    _width = width;
}

void Control::SetHeight(int height)
{
    _height = height;
}

void Control::SetPosition(const Coordinates& position)
{
    _position = position;
}

int Control::GetWight() const
{
    return _width;;
}

int Control::GetHeight() const
{
    return _height;
}

const Coordinates& Control::GetPosition() const
{
    return _position;
}