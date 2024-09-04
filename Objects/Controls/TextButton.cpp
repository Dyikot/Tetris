#include "TextButton.h"

TextButton::TextButton(const SDL_Point& position,
					   int width, 
					   int height,
					   const SDL_Color& background,
					   SDL_Color borderColor,
					   std::string_view text, 
					   const SDL_Color& fontColor,
					   int fontSize) noexcept:
	Button(position, width, height, background, borderColor),
	_textBlock(new TextBlock(position,
							 /*backgound*/ Colors::Transparent,
							 text, 
							 fontColor, 
							 fontSize))
{
	SetContent(_textBlock);
}

TextButton::TextButton(const SDL_Point& position, 
					   std::string_view text, 
					   const Style& style) noexcept:
	TextButton(position, 
			   style.Width,
			   style.Height,
			   style.Background,
			   style.BorderColor,
			   text, 
			   style.FontColor, 
			   style.FontSize)
{
	BackgroundOnHover = style.BackgroundOnHover;
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

void TextButton::SetText(std::string_view text)
{
	_textBlock->SetText(text);
}

void TextButton::OnContentOrPositionChange() noexcept
{
	if(_content != nullptr)
	{
		_content->SetPosition(
			{
				.x = _position.x + _width / 2,
				.y = _position.y + _height / 2 
			});
	}
}
