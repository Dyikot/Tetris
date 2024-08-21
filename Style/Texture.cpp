#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string_view path) noexcept
{
	_texture = IMG_LoadTexture(renderer, path.data());
	
	if(_texture == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

Texture::~Texture() noexcept
{
	SDL_DestroyTexture(_texture);
}

void Texture::Render(SDL_Renderer* renderer, const SDL_Rect& rectangle) const noexcept
{
	SDL_RenderCopy(renderer, _texture, NULL, &rectangle);
}

void Texture::SetColor(const SDL_Color& color)
{
	SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(_texture, color.a);
}