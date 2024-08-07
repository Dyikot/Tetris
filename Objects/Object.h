#pragma once

#include "SDL/SDL.h"
#include "../Application/Application.h"
#include "../BasicStructs/Coordinates.h"
#include "../Style/Color.h"

class Object
{
public:
	static constexpr Color DefaultBackgroundColor = Color::None;
protected:
	Color _backgroud;
	SDL_Renderer* _renderer = Application::Current()->GetRenderer();
public:
	Object(Color background = DefaultBackgroundColor);

	virtual ~Object() = default;

	virtual void Show() = 0;
		
	Color GetBackground() const;

	virtual void SetBackground(Color color);
};