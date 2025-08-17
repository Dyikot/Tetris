#include "Renderable.h"

void Renderable::SetRenderColor(SDL_Renderer* renderer, SDL_Color color) const noexcept
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}	
