#pragma once

#include "Button.h"
#include "TextBlock.h"

class TextButton: public Button
{
protected:
	TextBlock* _textBlock;
public:
	TextButton(SDL_Point position,
			   int width,
			   int height,
			   SDL_Color background,
			   SDL_Color borderColor,
			   std::string_view text,
			   SDL_Color fontColor,
			   int fontSize) noexcept;
	TextButton(SDL_Point position, std::string_view text, const Style& style) noexcept;

	void SetPosition(SDL_Point position) override;
	void SetContent(Control* content) noexcept;
	void SetText(std::string_view text);
protected:
	void OnContentOrPositionChange() noexcept;
};

