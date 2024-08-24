#pragma once

#include "Button.h"
#include "TextBlock.h"

class TextButton: public Button
{
protected:
	TextBlock* _textBlock;
public:
	TextButton(const SDL_Point& position,
			   int width,
			   int height,
			   const SDL_Color& background,
			   SDL_Color borderColor,
			   std::string_view text,
			   const SDL_Color& fontColor,
			   int fontSize) noexcept;

	TextButton(const SDL_Point& position, std::string_view text, const Style& style) noexcept;

	void SetPosition(const SDL_Point& position) noexcept override;

	void SetContent(Control* content) noexcept;

	void SetText(std::string_view text);
protected:
	void OnContentOrPositionChange() noexcept;
};

