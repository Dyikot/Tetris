#include "Button.h"


Button::Button(SDL_Point position,
			   int width, 
			   int height, 
			   SDL_Color background,
			   SDL_Color borderColor, 
			   Control* content) noexcept:
	Control(position, width, height, background),
	BorderColor(borderColor),
	_content(content)
{
}

Button::Button(SDL_Point position, const Style& style, Control* content) noexcept:
	Button(position, style.Width, style.Height, style.Background, style.BorderColor, content)
{
	BackgroundOnHover = style.BackgroundOnHover;
}

Button::~Button() noexcept
{
	delete _content;
}

void Button::SetContent(Control* content) noexcept
{
	delete _content;
	_content = content;
}

Control* Button::GetContent() const
{
	return _content;
}

void Button::Render(SDL_Renderer* renderer) const
{
	SDL_Rect rectangle =
	{
		.x = _position.x,
		.y = _position.y,
		.w = _width,
		.h = _height
	};

	// Border
	SetRenderColor(renderer, BorderColor);
	SDL_RenderDrawRect(renderer, &rectangle);

	// Backgroud
	SetRenderColor(renderer, _background);
	SDL_RenderFillRect(renderer, &rectangle);

	// Content
	_content->Render(renderer);
}

void Button::OnClick(const SDL_MouseButtonEvent& e)
{
	ClickSoundEffect.Play();

	if(Click)
	{
		Click(this, e);
	}
}
