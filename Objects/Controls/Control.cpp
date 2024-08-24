#include "Control.h"

Control::Control(const SDL_Point& position, 
                 int width,
                 int height, 
                 const SDL_Color& background) noexcept:
    _position(position),
    _width(width),
    _height(height),
    _background(background),
    _backgroundOffHover(background),
    BackgroundOnHover(background)
{
    
}

void Control::SetWidth(int width)
{
    _width = width;
}

void Control::SetHeight(int height)
{
    _height = height;
}

void Control::SetPosition(const SDL_Point& position)
{
    _position = position;
}

void Control::SetBackground(const SDL_Color& color)
{
    _backgroundOffHover = color;
}

int Control::GetWight() const
{
    return _width;
}

int Control::GetHeight() const
{
    return _height;
}

const SDL_Point& Control::GetPosition() const
{
    return _position;
}

const SDL_Color& Control::GetBackground() const
{
    return _background;
}

bool Control::IsMouseOver(const SDL_MouseButtonEvent& e)
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

    _background = BackgroundOnHover;
}

void Control::OnMouseLeave(const SDL_MouseButtonEvent& e)
{
    if(MouseLeave)
    {
        MouseLeave(this, e);
    }

    _background = _backgroundOffHover;
}