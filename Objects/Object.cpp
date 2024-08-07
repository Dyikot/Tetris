#include "Object.h"

Object::Object(Color background):
	_backgroud(background)
{
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

Color Object::GetBackground() const
{
	return _backgroud;
}

void Object::SetBackground(Color color)
{
	_backgroud = color;
}