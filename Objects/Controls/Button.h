#pragma once

#include "TextBlock.h"

class Button: public TextBlock
{
protected:
	Colors _borderColor;
public:
	Button(
		const Coordinates& position = { .x = 0, .y = 0 },
		int width = 120,
		int height = 40,
		Colors background = Colors::None,
		Colors borderColor = Colors::White,
		const std::string& text = "Кнопка",
		Colors textColor = Colors::Black,
		TTF_Font* font = TTF_OpenFont("Style\\Fonts\\segoeui.ttf", 24)
	):
		TextBlock(position, width, height, background, text, textColor, font),
		_borderColor(borderColor){}

	void Show() override;
};