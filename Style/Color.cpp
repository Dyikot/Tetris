#include "Color.h"

constexpr SDL_Color Colors::ToSDL_Color(Color color) noexcept
{
	return _colors[static_cast<int>(color)];
}

void Colors::SetRenderColor(SDL_Renderer* renderer, Color color) noexcept
{
	auto[r, g, b, a] = ToSDL_Color(color);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Colors::SetTextureColor(SDL_Texture* texture, Color color) noexcept
{
	auto [r, g, b, a] = ToSDL_Color(color);
	SDL_SetTextureColorMod(texture, r, g, b);
	SDL_SetTextureAlphaMod(texture, a);
}
