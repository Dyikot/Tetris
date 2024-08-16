#include "Control.h"

Control::Control(const SDL_Point& position, int width, int height, Color background) noexcept:
    UIElement(background),
    _position(position),
    _width(width),
    _height(height),
    _savedBackground(background),
    BackgroundColorOnHover(background)
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

void Control::SetBackground(Color color) noexcept
{
    Object::SetBackground(color);
    _savedBackground = color;
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

bool Control::IsMouseOver(const SDL_MouseButtonEvent& e) noexcept
{
    return e.x >= _position.x &&
           e.x <= _position.x + _width &&
           e.y >= _position.y &&
           e.y <= _position.y + _height;
}

void Control::OnMouseEnter(const SDL_MouseButtonEvent& e)
{
    if(MouseEnter)
    {
        MouseEnter(this, e);
    }

    _backgroud = BackgroundColorOnHover;
}

void Control::OnMouseLeave(const SDL_MouseButtonEvent& e)
{
    if(MouseLeave)
    {
        MouseLeave(this, e);
    }

    _backgroud = _savedBackground;
}