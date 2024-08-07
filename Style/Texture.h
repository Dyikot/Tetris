#pragma once

#include <string_view>
#include <iostream>

#include "SDL/SDL_image.h"

class Texture
{
private:
	SDL_Texture* _texture;
public:
	Texture(SDL_Renderer* renderer, std::string_view string_view) noexcept;

	~Texture() noexcept;

	void Render(SDL_Renderer* renderer, const SDL_Rect& rectangle) const noexcept;

	operator SDL_Texture*();
};

