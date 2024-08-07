#pragma once

#include "Control.h"
#include "SDL/SDL_ttf.h"

class TextBlock: public Control
{
public:
	static constexpr Color ActiveTextColor = Color::White;
	static constexpr Color InactiveTextColor = Color::Grey;
protected:
	std::string _text;
	Color _textColor;
	TTF_Font* _font;
	SDL_Surface* _textSurface;
	SDL_Texture* _textTexture;
private:
	const int Width = 0;
	const int Height = 0;
public:
	TextBlock(const Coordinates& position,
			  Color background,
			  const std::string& text,
			  Color textColor,
			  int textSize) noexcept;	

	virtual ~TextBlock();

	void Show() noexcept override;

	void SetText(const std::string& text) noexcept;

	void SetTextColor(Color textColor) noexcept;	

	const std::string& GetText() const noexcept;

	Color GetTextColor() const noexcept;

protected:
	TextBlock(const Coordinates& position,
			  int width,
			  int height,
			  Color background,
			  const std::string& text,
			  Color textColor,
			  int textSize) noexcept;
};
