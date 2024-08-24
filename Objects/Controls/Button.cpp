#include "Button.h"


Button::Button(const SDL_Point& position,
			   int width, 
			   int height, 
			   const SDL_Color& background,
			   SDL_Color borderColor, 
			   Control* content) noexcept:
	Control(position, width, height, background),
	BorderColor(borderColor),
	_content(content)
{
	
}

Button::Button(const SDL_Point& position, const Style& style, Control* content) noexcept:
	Button(position, style.Width, style.Height, style.Background, style.BorderColor, content)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

Button::~Button() noexcept
{
	delete _content;
}

void Button::Show() const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	// Border
	SetRenderColor(_renderer, BorderColor);
	SDL_RenderDrawRect(_renderer, &rectangle);

	// Backgroud
	SetRenderColor(_renderer, _background);
	SDL_RenderFillRect(_renderer, &rectangle);

	// Content
	_content->Show();
}


void Button::SetContent(Control* content) noexcept
{
	delete _content;
	_content = content;
}

Control* const Button::GetContent() const
{
	return _content;
}

void Button::OnClick(const SDL_MouseButtonEvent& e)
{
	if(Click)
	{
		Click(this, e);
	}
}
