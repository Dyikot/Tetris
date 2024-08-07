#include "Object.h"

Object::Object(Color background) noexcept:
	_backgroud(background)
{
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

Color Object::GetBackground() const noexcept
{
	return _backgroud;
}

void Object::SetBackground(Color color) noexcept
{
	_backgroud = color;
}