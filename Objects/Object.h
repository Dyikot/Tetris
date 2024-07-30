#pragma once

#include "SDL/SDL.h"
#include "..\Application\Application.h"
#include "..\BasicStructs\Coordinates.h"
#include "..\Style\Color\Color.h"

class Object
{
public:
	static constexpr Colors DefaultBackgroundColor = Colors::None;
protected:
	Colors _backgroud;
	SDL_Renderer* _renderer = Application::Current()->GetRenderer();
public:
	Object(Colors background = DefaultBackgroundColor):
		_backgroud(background){}

	virtual ~Object() = default;

	virtual void Show() = 0;
		
	Colors GetBackground() const;

	virtual void SetBackground(Colors color);
};