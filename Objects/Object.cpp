#include "Object.h"

Colors Object::GetBackground() const
{
	return _backgroud;
}

void Object::SetBackground(Colors color)
{
	_backgroud = color;
}