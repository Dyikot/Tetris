#include "Control.h"

Control::Control(const SDL_Point& position, int width, int height, Color background) noexcept:
    _position(position),
    _width(width),
    _height(height),
    Object(background)
{

}

void Control::SetWidth(int width) noexcept
{
    _width = width;
}

void Control::SetHeight(int height) noexcept
{
    _height = height;
}

void Control::SetPosition(const SDL_Point& position) noexcept
{
    _position = position;
}

int Control::GetWight() const noexcept
{
    return _width;
}

int Control::GetHeight() const noexcept
{
    return _height;
}

const SDL_Point& Control::GetPosition() const noexcept
{
    return _position;
}

bool Control::IsInRange(const SDL_Point& position) const noexcept
{
    return position.x >= _position.x &&
           position.x <= _position.x + _width &&
           position.y >= _position.y &&
           position.y <= _position.y + _height;
}

bool Control::IsInRange(const int x, const int y) const noexcept
{
    return IsInRange({ x, y });
}
