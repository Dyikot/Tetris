#pragma once

#include "Button.h"
#include "../TextBlock.h"

class TextButton: public Button
{
public:
	static constexpr int DefaultTextSize = 24;
protected:
	TextBlock _textBlock;
public:
	TextButton(const SDL_Point& position,
			   int width,
			   int height,
			   const SDL_Color& background,
			   SDL_Color borderColor,
			   const std::string& text,
			   const SDL_Color& fontColor,
			   int fontSize) noexcept;

	void SetPosition(const SDL_Point& position) noexcept override;

	void SetContent(Control* content) noexcept;
protected:
	void OnContentOrPositionChange() noexcept;
};

