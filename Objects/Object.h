#pragma once

#include "SDL/SDL.h"
#include "../Application/Application.h"
#include "../Graphics/Colors.h"

class Object
{
protected:	
	SDL_Renderer* _renderer = Application::Current()->GetRenderer();
public:
	virtual ~Object() = default;

	virtual void Show() const = 0;
};