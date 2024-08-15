#include "Image.h"

Image::Image(const SDL_Point& position,
	int width,
	int height, 
	Color background,
	Texture* texture) noexcept:
	Control(position, width, height, background),
	_texture(texture)
{
	
}

void Image::Show() const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	Colors::SetTextureColor(*_texture, _backgroud);
	_texture->Render(_renderer, rectangle);
}

void Image::SetTexture(Texture* texture)
{
	_texture = texture;
}

Texture* Image::GetTexture() const
{
	return _texture;
}
