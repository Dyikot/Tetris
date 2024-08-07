#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string_view string_view) noexcept
{
	_texture = IMG_LoadTexture(renderer, string_view.data());
	
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

Texture::operator SDL_Texture*()
{
	return _texture;
}
