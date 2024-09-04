#pragma once

#include <string_view>
#include <iostream>

#include "SDL/SDL_image.h"

class Texture
{
private:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
public:
	Texture(SDL_Renderer* renderer, std::string_view path) noexcept;

	Texture(SDL_Renderer* renderer, SDL_Texture* texture) noexcept;

	~Texture() noexcept;

	void Render(const SDL_Rect& rectangle) const noexcept;

	void SetColor(const SDL_Color& color) noexcept;

	bool IsEmpty() const noexcept;

	std::pair<int, int> QuerySize() const noexcept;

	Texture& operator=(SDL_Texture* texture);
};

