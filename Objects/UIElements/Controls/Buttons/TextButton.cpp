#include "TextButton.h"

TextButton::TextButton(const SDL_Point& position,
	int width, 
	int height,
	const SDL_Color& background,
	SDL_Color borderColor,
	const std::string& text, 
	const SDL_Color& fontColor,
	int fontSize) noexcept:
	Button(position, width, height, background, borderColor),
	_textBlock(position, DefaultBackgroundColor, text, fontColor, fontSize)
{
	SetContent(&_textBlock);
	BackgroundOnHover = Colors::Green;
}

void TextButton::SetPosition(const SDL_Point& position) noexcept
{
	Button::SetPosition(position);
	OnContentOrPositionChange();
}

void TextButton::SetContent(Control* content) noexcept
{
	Button::SetContent(content);
	OnContentOrPositionChange();
}

void TextButton::OnContentOrPositionChange() noexcept
{
	if(_content != nullptr)
	{
		_content->SetPosition({ .x = _position.x + _width / 2,
								.y = _position.y + _height / 2 });
	}
}
