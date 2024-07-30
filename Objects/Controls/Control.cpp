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
    return _width;
}

int Control::GetHeight() const
{
    return _height;
}

const Coordinates& Control::GetPosition() const
{
    return _position;
}

bool Control::IsInRange(const Coordinates& position) const
{
    return position.x >= _position.x &&
           position.x <= _position.x + _width &&
           position.y >= _position.y &&
           position.y <= _position.y + _height;
}

bool Control::IsInRange(const int x, const int y) const
{
    return IsInRange({ x, y });
}
