#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer, std::string_view path) noexcept:
	_renderer(renderer)
{
	_texture = IMG_LoadTexture(_renderer, path.data());
	
	if(_texture == nullptr)
	{
		std::cout << SDL_GetError() << '\n';
	}
}

Texture::Texture(SDL_Renderer* renderer, SDL_Texture* texture) noexcept
{
	_renderer = renderer;
	_texture = texture;
}

Texture::~Texture() noexcept
{
	SDL_DestroyTexture(_texture);
}

void Texture::Render(const SDL_Rect& rectangle) const noexcept
{
	SDL_RenderCopy(_renderer, _texture, NULL, &rectangle);
}

void Texture::SetColor(const SDL_Color& color) noexcept
{
	SDL_SetTextureColorMod(_texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(_texture, color.a);
}

bool Texture::IsEmpty() const noexcept
{
	return _texture == nullptr;
}

std::pair<int, int> Texture::QuerySize() const noexcept
{
	int width = 0;
	int height = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
	return { width, height };
}

Texture& Texture::operator=(SDL_Texture* texture)
{
	SDL_DestroyTexture(_texture);
	_texture = texture;

	return *this;
}
