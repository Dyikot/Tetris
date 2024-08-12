#include "TextButton.h"

TextButton::TextButton(const SDL_Point& position,
	int width, 
	int height,
	Color background,
	Color borderColor,
	const std::string& text, 
	Color textColor,
	int textSize) noexcept:
	Button(position, width, height, background, borderColor),
	_textBlock(position, DefaultBackgroundColor, text, textColor, textSize)
{
	SetContent(&_textBlock);
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
	if(GetContent() != nullptr)
	{
		GetContent()->SetPosition({ .x = _position.x + _width / 2,
									.y = _position.y + _height / 2 });
	}
}
