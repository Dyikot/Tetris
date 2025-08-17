#pragma once

#include "SDL/SDL_render.h"

class Renderable
{
public:
	virtual ~Renderable() = default;

	virtual void Render(SDL_Renderer* renderer) const = 0;
protected:
	void SetRenderColor(SDL_Renderer* renderer, SDL_Color color) const noexcept;
};