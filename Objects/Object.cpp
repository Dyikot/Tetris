#include "Object.h"

Object::Object(const SDL_Color& background) noexcept:
	_backgroud(background)
{
	
}

const SDL_Color& Object::GetBackground() const noexcept
{
	return _backgroud;
}

void Object::SetBackground(const SDL_Color& color) noexcept
{
	_backgroud = color;
}