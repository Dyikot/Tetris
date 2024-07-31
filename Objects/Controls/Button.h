#pragma once

#include "TextBlock.h"

class Button: public TextBlock
{
public:
	static constexpr int DefaultTextSize = 24;
	static constexpr Color DefaultBorderColor = Color::Green;
protected:
	Color _borderColor;
	Color _backgroundSaved;
public:
	Button(const Coordinates& position,
		   int width,
		   int height,
		   Color background,
		   Color borderColor,
		   const std::string& text,
		   Color textColor,
		   int textSize
	):
		TextBlock(position, width, height, background, text, textColor, textSize),
		_borderColor(borderColor),
		_backgroundSaved(background){}

	void Show() override;

	void SetBackground(Color color) override;
	
	void OnHover();

	void OnLeave();
};