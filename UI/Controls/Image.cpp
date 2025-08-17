#include "Image.h"
#include "../../Application/Application.h"

Image::Image(SDL_Point position,
			 int width,
			 int height, 
			 SDL_Color background,
			 std::string_view path) noexcept:
	Control(position, width, height, background),
	_texture(Application::Current()->GetWindow()->Renderer, path)
{
	_texture.SetColor(_background);
}

Image::Image(SDL_Point position,
			 int width, 
			 int height, 
			 std::string_view path) noexcept:
	Image(position, width, height, Colors::Transparent, path)
{}

Image::Image(SDL_Point position, std::string_view path) noexcept:
	Image(position, 0, 0, Colors::Transparent, path)
{
	auto [width, height] = _texture.Size();
	_width = width;
	_height = height;
}

Image::Image(SDL_Point position, 
			 std::string_view path,
			 const Style& style) noexcept:
	Image(position, style.Width, style.Height, style.Background, path)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

void Image::Render(SDL_Renderer* renderer) const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	_texture.Render(renderer, rectangle);
}

void Image::SetBackground(SDL_Color color)
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