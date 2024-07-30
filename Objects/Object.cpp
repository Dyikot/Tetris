#include "Object.h"

Object::Object(Colors background)
{
	_backgroud = background;
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
}

Colors Object::GetBackground() const
{
	return _backgroud;
}

void Object::SetBackground(Colors color)
{
	_backgroud = color;
}