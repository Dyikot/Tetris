#include "Object.h"

Object::Object(Color background) noexcept:
	_backgroud(background)
{
	
}

Color Object::GetBackground() const noexcept
{
	return _backgroud;
}

void Object::SetBackground(Color color) noexcept
{
	_backgroud = color;
}