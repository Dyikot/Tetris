#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string_view string_view)
{
	_texture = IMG_LoadTexture(renderer, string_view.data());

	if(_texture == nullptr)
	{
		std::cout << "Не удалось создать текстуру: " << SDL_GetError() << '\n';
	}
}

Texture::~Texture()
{
	SDL_DestroyTexture(_texture);
}

void Texture::Render(SDL_Renderer* renderer, const SDL_Rect& rectangle) const
{
	SDL_RenderCopy(renderer, _texture, NULL, &rectangle);
}

Texture::operator SDL_Texture*()
{
	return _texture;
}
