#include "Color.h"

constexpr SDL_Color Colors::ToSDL_Color(Color color)
{
	return _colors[static_cast<int>(color)];
}

void Colors::SetRenderColor(SDL_Renderer* renderer, Color color)
{
	auto[r, g, b, a] = ToSDL_Color(color);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
