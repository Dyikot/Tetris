#pragma once

#include <string_view>
#include <iostream>

#include "SDL/SDL_image.h"

class Texture
{
private:
	SDL_Texture* _texture;
public:
	Texture(SDL_Renderer* renderer, std::string_view string_view);

	~Texture();

	void Render(SDL_Renderer* renderer, const SDL_Rect& rectangle) const;

	operator SDL_Texture*();
};

