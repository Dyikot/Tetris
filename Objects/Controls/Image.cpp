#include "Image.h"

Image::Image(const SDL_Point& position,
			 int width,
			 int height, 
			 const SDL_Color& background,
			 std::string_view path) noexcept:
	Control(position, width, height, background),
	_texture(_renderer, path)
{
	_texture.SetColor(_background);
}

Image::Image(const SDL_Point& position,
			 int width, 
			 int height, 
			 std::string_view path) noexcept:
	Image(position, width, height, Colors::Transparent, path)
{
	
}

Image::Image(const SDL_Point& position, std::string_view path) noexcept:
	Image(position, /*width*/ 0, /*height*/ 0, Colors::Transparent, path)
{
	auto [width, height] = _texture.QuerySize();
	_width = width;
	_height = height;
}

Image::Image(const SDL_Point& position, 
			 std::string_view path,
			 const Style& style) noexcept:
	Image(position, style.Width, style.Height, style.Background, path)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

void Image::OnRender() const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	_texture.Render(rectangle);
}

void Image::SetBackground(const SDL_Color& color)
{
	Control::SetBackground(color);
	_texture.SetColor(color);
}

void Image::OnMouseEnter(const SDL_MouseButtonEvent& e)
{
	Control::OnMouseEnter(e);
	_texture.SetColor(_background);
}

void Image::OnMouseLeave(const SDL_MouseButtonEvent & e)
{
	Control::OnMouseLeave(e);
	_texture.SetColor(_background);
}