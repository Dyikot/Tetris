#pragma once

#include "SDL/SDL.h"

class Object
{
protected:
	SDL_Renderer* _renderer;
public:
	Object() noexcept;

	virtual ~Object() = default;

	virtual void OnRender() const = 0;
protected:
	void SetRenderColor(const SDL_Color& color) const noexcept;
};